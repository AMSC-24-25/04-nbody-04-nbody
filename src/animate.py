from itertools import groupby
from sys import argv, exit
from PIL import Image, ImageDraw
import math

# Parse Command Line Arguments
if len(argv) < 3:
    exit("Usage is render.py <input file> <output file>")

input_file = argv[1]
output_file = argv[2]

def circle_to_box(center_x, center_y, size):
    return (center_x - size, center_y - size,
            center_x + size, center_y + size)

# Process the file
with open(input_file, 'r') as f:
    num_parts, box_size = next(f).split()
    num_parts, box_size = int(num_parts), float(box_size)
    
    # Store all frames' coordinates first
    all_frames_coords = []
    file_sections = groupby(f, lambda x: x and not x.isspace())
    frame_sections = (x[1] for x in file_sections if x[0])
    
    for frame_section in frame_sections:
        coords = [list(map(float, line.split())) for line in frame_section]
        all_frames_coords.append(coords)

    # Calculate global min/max for consistent scaling
    all_x = [coord[0] for frame in all_frames_coords for coord in frame]
    all_y = [coord[1] for frame in all_frames_coords for coord in frame]
    global_x_min, global_x_max = min(all_x), max(all_x)
    global_y_min, global_y_max = min(all_y), max(all_y)
    
    # Calculate scaling factors
    x_range = global_x_max - global_x_min
    y_range = global_y_max - global_y_min
    scale = min(1848 / x_range, 1848 / y_range)  # Leave 100px margin on each side
    
    def transform_coords(x, y):
        # Center the particles in the image
        scaled_x = (x - global_x_min) * scale + 100
        scaled_y = (y - global_y_min) * scale + 100
        return scaled_x, scaled_y

    frames = []
    trail_length = 10  # Number of previous positions to keep for trail effect
    
    # Particle colors with alpha channel
    colors = [
        (255, 0, 0),    # Red
        (0, 0, 255),    # Blue
        (0, 255, 0),    # Green
        (128, 0, 128)   # Purple
    ]
    
    # Process each frame
    for frame_idx, coordinates in enumerate(all_frames_coords):
        # Create frame with black background
        img = Image.new('RGB', (2048, 2048), 'black')
        drawer = ImageDraw.Draw(img)
        
        # Draw trails and particles
        for particle_idx, (x, y) in enumerate(coordinates):
            color = colors[particle_idx % len(colors)]
            
            # Transform current coordinates
            current_x, current_y = transform_coords(x, y)
            
            # Draw the main particle
            particle_radius = 8
            drawer.ellipse(circle_to_box(current_x, current_y, particle_radius), 
                         fill=color)
            
            # Draw a glow effect around the particle
            for glow_size in range(particle_radius + 8, particle_radius + 2, -2):
                alpha = int(100 * (1 - (glow_size - particle_radius) / 8))
                glow_color = tuple(int(c * alpha / 100) for c in color)
                drawer.ellipse(circle_to_box(current_x, current_y, glow_size),
                             fill=None, outline=glow_color)
        
        frames.append(img)

    # Save the animation
    print(f"Saving animation with {len(frames)} frames...")
    frames[0].save(
        output_file,
        format='GIF',
        append_images=frames[1:],
        save_all=True,
        duration=50,  # Faster animation
        loop=0
    )