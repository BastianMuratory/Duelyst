from PIL import Image
from os import listdir
from os.path import isfile, join

def add_outline_8neighbours(image_path, output_path, outline_color=(0, 0, 0)):
    # Open the image
    img = Image.open(image_path)
    
    # Convert the image to RGBA if it's not already
    img = img.convert("RGBA")
    
    # Get the image data as a list of tuples
    data = list(img.getdata())
    
    # Create a new list for the modified data
    new_data = []

    # Define the transparency threshold (you can adjust this)
    transparency_threshold = 200

    # Loop through each pixel in the image
    for y in range(img.height):
        for x in range(img.width):
            pixel = data[y * img.width + x]

            # Check if the pixel is mostly transparent
            if pixel[3] < transparency_threshold:
                # If it's mostly transparent, check its neighbors
                has_colored_neighbor = any(
                    data[(y + dy) * img.width + (x + dx)][3] >= transparency_threshold
                    for dx in [-1, 0, 1] for dy in [-1, 0, 1]
                    if 0 <= x + dx < img.width and 0 <= y + dy < img.height
                )

                # If it has a colored neighbor, replace with the outline color
                if has_colored_neighbor:
                    new_data.append(outline_color)
                else:
                    new_data.append(pixel)
            else:
                # If it's not transparent, keep the original color
                new_data.append(pixel)

    # Create a new image with the modified data
    new_img = Image.new("RGBA", img.size)
    new_img.putdata(new_data)

    # Save the new image with an outline
    new_img.save(output_path, "PNG")


def add_outline_4neighbours(image_path, output_path, outline_color=(0, 0, 0)):
    # Open the image
    img = Image.open(image_path)

    # Convert the image to RGBA if it's not already
    img = img.convert("RGBA")

    # Get the image data as a list of tuples
    data = list(img.getdata())

    # Create a new list for the modified data
    new_data = []

    # Define the transparency threshold (you can adjust this)
    transparency_threshold = 200

    # Loop through each pixel in the image
    for y in range(img.height):
        for x in range(img.width):
            pixel = data[y * img.width + x]

            # Check if the pixel is mostly transparent
            if pixel[3] < transparency_threshold:
                # If it's mostly transparent, check its top, bottom, left, and right neighbors

                # Define neighbors and handle edges gracefully
                neighbors = [
                    data[(y - 1) * img.width + x] if y - 1 >= 0 else (0, 0, 0, 0),  # top
                    data[(y + 1) * img.width + x] if y + 1 < img.height else (0, 0, 0, 0),  # bottom
                    data[y * img.width + (x - 1)] if x - 1 >= 0 else (0, 0, 0, 0),  # left
                    data[y * img.width + (x + 1)] if x + 1 < img.width else (0, 0, 0, 0),  # right
                ]

                # If any neighbor is colored, replace with the outline color
                if any(neighbor[3] >= transparency_threshold for neighbor in neighbors):
                    new_data.append(outline_color)
                else:
                    new_data.append(pixel)
            else:
                # If it's not transparent, keep the original color
                new_data.append(pixel)

    # Create a new image with the modified data
    new_img = Image.new("RGBA", img.size)
    new_img.putdata(new_data)

    # Save the new image with an outline
    new_img.save(output_path, "PNG")


#add_outline_8neighbours("f1_general.png", "output_sprite_with_8_outline.png")

folderPath = "troopAnimations4"
onlyfiles = [f for f in listdir(folderPath) if (isfile(join(folderPath, f)) and ".png" in f)]

i=0
for f in onlyfiles :
    i+=1
    fullPath = folderPath + "/" + f
    print(f"{f} {i}{len(onlyfiles)}")
    add_outline_4neighbours(fullPath, fullPath, outline_color=(0, 0, 0))

