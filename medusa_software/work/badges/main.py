#!/usr/bin/python3

from PIL import Image, ImageDraw, ImageFont
import sys, os

supersample = 8
#final_size = (128, 32)

def get_text_dimensions(text_string, font):
	# https://stackoverflow.com/a/46220683/9263761
	ascent, descent = font.getmetrics()

	text_width = font.getmask(text_string).getbbox()[2]
	text_height = font.getmask(text_string).getbbox()[3] + descent

	return (text_width, text_height)

def main(args):
	if not (os.path.exists("pil")):
		os.mkdir("pil")

	font = ImageFont.truetype(font="../../submodules/source-code-pro/TTF/SourceCodePro-Regular.ttf", size=16 * supersample)
	text = "Hello | Deez"

	final_size = get_text_dimensions(text, font)
	final_size = [(final_size[0] + (16 * supersample)) // supersample, (final_size[1] + (6 * supersample)) // supersample]

	img = Image.new('RGBA', (final_size[0] * supersample, final_size[1] * supersample))
	img.putalpha(256)
	draw = ImageDraw.Draw(img)
	draw.rounded_rectangle((0, 0, final_size[0] * supersample, final_size[1] * supersample), fill="#202020", outline="#f0f0f0", width=2 * supersample, radius=8 * supersample)

	draw.text((8 * supersample, 2 * supersample), "Hello | Deez", font=font, fill=(255, 255, 255, 255))

	img = img.resize(final_size, resample=Image.LANCZOS)

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