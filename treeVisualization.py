from graphviz import Source


def visualize_bst(dot_file):
    print(f"Loading DOT file: {dot_file}")

    # Load the DOT file
    src = Source.from_file(dot_file)

    # Define output paths
    output_path = "/Users/frankbernal/CLionProjects/Csci115FinalProject/avl_tree_after"
    print(f"Rendering output to: {output_path}.png")

    # Render the tree to a PNG file
    src.render(output_path, format="png", cleanup=True)

    # Open the PNG file in the default viewer
    print(f"Opening the rendered tree")
    src.view()


# Call the function with the full path to your .dot file
visualize_bst("/Users/frankbernal/CLionProjects/Csci115FinalProject/avl_tree_after.dot")
