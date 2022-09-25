#!/usr/bin/python3

from PIL import Image, ImageDraw
import sys, os

supersample = 8
final_size = (128, 32)

def main(args):
	if not (os.path.exists("pil")):
		os.mkdir("pil")
	img = Image.new('RGBA', (final_size[0] * supersample, final_size[1] * supersample))
	img.putalpha(256)
	draw = ImageDraw.Draw(img)
	draw.rounded_rectangle((0, 0, final_size[0] * supersample, final_size[1] * supersample), fill="#202020", outline="#f0f0f0", width=2 * supersample, radius=8 * supersample)

	img = img.resize(final_size, resample=Image.Resampling.LANCZOS)

	img.save('pil/pil_testaa.png')
	print(args)


	if not (os.path.exists("pil")):
		os.mkdir("pil")
	img = Image.new('RGBA', (final_size[0], final_size[1]))
	img.putalpha(256)
	draw = ImageDraw.Draw(img)
	draw.rounded_rectangle((0, 0, final_size[0], final_size[1]), fill="#202020", outline="#f0f0f0", width=2, radius=8)

	img.save('pil/pil_test.png')
	print(args)

if __name__ == "__main__":
	main(sys.argv)