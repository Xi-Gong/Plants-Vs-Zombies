#!/usr/bin/env python
import os
import sys
from PIL import Image
from xml.etree import ElementTree
import json


def tree_to_dict(tree):
    d = {}
    for index, item in enumerate(tree):
        if item.tag == 'key':
            if tree[index + 1].tag == 'string':
                d[item.text] = tree[index + 1].text
            elif tree[index + 1].tag == 'true':
                d[item.text] = True
            elif tree[index + 1].tag == 'false':
                d[item.text] = False
            elif tree[index + 1].tag == 'integer':
                d[item.text] = int(tree[index + 1].text);
            elif tree[index + 1].tag == 'dict':
                d[item.text] = tree_to_dict(tree[index + 1])
    return d


def frames_from_data(filename, ext):
    data_filename = filename + ext
    if ext == '.plist':
        root = ElementTree.fromstring(open(data_filename, 'r').read())
        plist_dict = tree_to_dict(root[0])
        to_list = lambda x: x.replace('{', '').replace('}', '').split(',')
        frames = plist_dict['frames'].items()
        for k, v in frames:
            frame = v
            if(plist_dict["metadata"]["format"] == 3):
                frame['frame'] = frame['textureRect']
                frame['rotated'] = frame['textureRotated']
                frame['sourceSize'] = frame['spriteSourceSize']
                frame['offset'] = frame['spriteOffset']

            rectlist = to_list(frame['frame'])
            width = int(float(rectlist[3] if frame['rotated'] else rectlist[2]))
            height = int(float(rectlist[2] if frame['rotated'] else rectlist[3]))
            frame['box'] = (
                int(float(rectlist[0])),
                int(float(rectlist[1])),
                int(float(rectlist[0])) + width,
                int(float(rectlist[1])) + height
            )
            real_rectlist = to_list(frame['sourceSize'])
            real_width = int(float(real_rectlist[1] if frame['rotated'] else real_rectlist[0]))
            real_height = int(float(real_rectlist[0] if frame['rotated'] else real_rectlist[1]))
            real_sizelist = [real_width, real_height]
            frame['real_sizelist'] = real_sizelist
            offsetlist = to_list(frame['offset'])
            offset_x = int(float(offsetlist[1] if frame['rotated'] else offsetlist[0]))
            offset_y = int(float(offsetlist[0] if frame['rotated'] else offsetlist[1]))

            if frame['rotated']:
                frame['result_box'] = (
                    int(float((real_sizelist[0] - width) / 2 + offset_x)),
                    int(float((real_sizelist[1] - height) / 2 + offset_y)),
                    int(float((real_sizelist[0] + width) / 2 + offset_x)),
                    int(float((real_sizelist[1] + height) / 2 + offset_y))
                )
            else:
                frame['result_box'] = (
                    int(float((real_sizelist[0] - width) / 2 + offset_x)),
                    int(float((real_sizelist[1] - height) / 2 - offset_y)),
                    int(float((real_sizelist[0] + width) / 2 + offset_x)),
                    int(float((real_sizelist[1] + height) / 2 - offset_y))
                )
        return frames

    elif ext == '.json':
        json_data = open(data_filename)
        data = json.load(json_data)
        frames = {}
        for f in data['frames']:
            x = int(float(f["frame"]["x"]))
            y = int(float(f["frame"]["y"]))
            w = int(float(f["frame"]["h"] if f['rotated'] else f["frame"]["w"]))
            h = int(float(f["frame"]["w"] if f['rotated'] else f["frame"]["h"]))
            real_w = int(float(f["sourceSize"]["h"] if f['rotated'] else f["sourceSize"]["w"]))
            real_h = int(float(f["sourceSize"]["w"] if f['rotated'] else f["sourceSize"]["h"]))
            d = {
                'box': (
                    x,
                    y,
                    x + w,
                    y + h
                ),
                'real_sizelist': [
                    real_w,
                    real_h
                ],
                'result_box': (
                    int((real_w - w) / 2),
                    int((real_h - h) / 2),
                    int((real_w + w) / 2),
                    int((real_h + h) / 2)
                ),
                'rotated': f['rotated']
            }
            frames[f["filename"]] = d
        json_data.close()
        return frames.items()
    else:
        print("Wrong data format on parsing: '" + ext + "'!")
        exit(1)


def gen_png_from_data(filename, ext):
    big_image = Image.open(filename + ".png")
    frames = frames_from_data(filename, ext)
    for k, v in frames:
        frame = v
        box = frame['box']
        rect_on_big = big_image.crop(box)
        real_sizelist = frame['real_sizelist']
        result_image = Image.new('RGBA', real_sizelist, (0, 0, 0, 0))
        result_box = frame['result_box']
        result_image.paste(rect_on_big, result_box, mask=0)
        if frame['rotated']:
            result_image = result_image.transpose(Image.ROTATE_90)
        if not os.path.isdir(filename):
            os.mkdir(filename)
        outfile = (filename + '/' + k).replace('gift_', '')
        if not outfile.endswith('.png'):
            outfile += '.png'
        print(outfile, "generated")
        result_image.save(outfile)


def endWith(s,*endstring):
    array = map(s.endswith,endstring)
    if True in array:
        return True
    else:
        return False


# Get the all files & directories in the specified directory (path).   
def get_file_list(path):
    current_files = os.listdir(path)
    all_files = []  
    for file_name in current_files:
        full_file_name = os.path.join(path, file_name)
        if endWith(full_file_name,'.plist'):
            full_file_name = full_file_name.replace('.plist','')
            all_files.append(full_file_name)
        if endWith(full_file_name,'.json'):
            full_file_name = full_file_name.replace('.json','')
            all_files.append(full_file_name)
        if os.path.isdir(full_file_name):
            next_level_files = get_recursive_file_list(full_file_name)
            all_files.extend(next_level_files)
    return all_files


def get_sources_file(filename):
    data_filename = filename + ext
    png_filename = filename + '.png'
    if os.path.exists(data_filename) and os.path.exists(png_filename):
        gen_png_from_data(filename, ext)
    else:
        print("Make sure you have both " + data_filename + " and " + png_filename + " files in the same directory")


# Use like this: python unpacker.py [Image Path or Image Name(but no suffix)] [Type:plist or json]
if __name__ == '__main__':
    if len(sys.argv) <= 1:
        print("You must pass filename as the first parameter!")
        exit(1)
    # filename = sys.argv[1]
    path_or_name = sys.argv[1]
    ext = '.plist'
    if len(sys.argv) < 3:
        print("No data format passed, assuming .plist")
    elif sys.argv[2] == 'plist':
        print(".plist data format passed")
    elif sys.argv[2] == 'json':
        ext = '.json'
        print(".json data format passed")
    else:
        print("Wrong data format passed '" + sys.argv[2] + "'!")
        exit(1)
    # supports multiple file conversions
    if os.path.isdir(path_or_name):
        files = get_file_list(path_or_name)
        for file0 in files:
            get_sources_file(file0)
    else:
        get_sources_file(path_or_name)
