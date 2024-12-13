import matplotlib.pyplot as plt
import matplotlib.animation as animation

def read_sorting_steps(filename):
    with open(filename, "r") as file:
        steps = [list(map(int, line.strip().split(","))) for line in file]
    return steps

def visualize_sorting(steps):
    fig, ax = plt.subplots()
    bar_rects = ax.bar(range(len(steps[0])), steps[0], align="edge", color="skyblue")
    ax.set_xlim(0, len(steps[0]))
    ax.set_ylim(0, max(max(steps)) + 1)

    def update(step):
        for rect, height in zip(bar_rects, step):
            rect.set_height(height)

    ani = animation.FuncAnimation(
        fig, update, frames=steps, repeat=False, interval=300, blit=False
    )

    ani.save("merge_sort_visualization.mp4", writer="ffmpeg", fps=120)

    plt.show()

if __name__ == "__main__":
    steps = read_sorting_steps("sorting_steps.txt")
    visualize_sorting(steps)
