#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import pandas as pd

# Parametri configurabili
csv_file = "./build/output.csv"

# Carica i dati dal CSV
data = pd.read_csv(csv_file)

# Determina dimensioni e numero di particelle
dimensions = (len(data.columns) - 2) // 2  # Esclude step e particle_id
particle_ids = data['particle_id'].unique()
num_particles = len(particle_ids)

# Prepara le traiettorie
trajectories = {
    particle_id: data[data['particle_id'] == particle_id][[f'position_{dim}' for dim in range(dimensions)]].values
    for particle_id in particle_ids
}

# Imposta i limiti degli assi (facoltativo, adattabile ai dati)
x_limits = (-5, 5)
y_limits = (-5, 5)

# Configura il grafico
fig, ax = plt.subplots()
ax.set_xlim(*x_limits)
ax.set_ylim(*y_limits)
ax.set_aspect('equal')
lines = {particle_id: ax.plot([], [], label=f"Particle {particle_id}")[0] for particle_id in particle_ids}

# Traccia un cerchio (opzionale, per esempio un'orbita)
theta = np.linspace(0, 2 * np.pi, 100)
circle_radius = 4
ax.plot(circle_radius * np.cos(theta), circle_radius * np.sin(theta), linewidth=1, linestyle='--', color='gray')

# Funzione di inizializzazione
def init():
    for line in lines.values():
        line.set_data([], [])
    return lines.values()

# Funzione di aggiornamento per ogni frame
def update(frame):
    for particle_id, line in lines.items():
        trajectory = trajectories[particle_id]
        if frame < len(trajectory):
            line.set_data(trajectory[:frame, 0], trajectory[:frame, 1])  # Assume 2D
    return lines.values()

# Creazione dell'animazione
frames = max(len(trajectory) for trajectory in trajectories.values())
ani = FuncAnimation(fig, update, frames=frames, init_func=init, interval=100, blit=True)

# Mostra il grafico
plt.legend()
plt.show()