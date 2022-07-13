#!/usr/bin/python3

from PIL import Image, ImageDraw
import sys, os

def main(args):
	if not (os.path.exists("pil")):
		os.mkdir("pil")
	img = Image.new('RGBA', (128, 32))
	img.putalpha(256)
	draw = ImageDraw.Draw(img)
	draw.rounded_rectangle((0, 0, 128, 32), fill="#202020", outline="#f0f0f0", width=2, radius=8)
	img.save('pil/pil_test.png')
	print(args)

if __name__ == "__main__":
	main(sys.argv)