# Analysis of Relationships with the PageRank Algorithm ✨

Welcome to the project on the analysis of applications of the PageRank algorithm, implemented in the robust C programming language. This innovative project 🚀 opens a wide range of possibilities for analyzing the relative importance of nodes within a network and offers a creative and efficient approach to understanding complex interactions in various contexts, from evaluating web links to analyzing teamwork dynamics and beyond.

## Project Features:

- **Versatile Implementation of the PageRank Algorithm:** Applies the PageRank algorithm to assess the importance or prestige of nodes in a network 🌐, allowing its application in a variety of fields such as social network analysis, SEO, academic research, and more.

- **Modular Design:** Code organized into functions and modular files 📁, which facilitates understanding, management, and customization of the project.

- **User-Friendly Interface:** Developed with an intuitive user interface 🖥️ that makes the project accessible to people with varying levels of technical skill.

- **Ease of Customization and Expansion:** The project's architecture allows for easy adaptation to different use cases, making it a versatile tool for relationship analysis in any type of network 🔧.

## Getting Started:

Follow these steps to prepare and execute the project, allowing you to begin analyzing the relationships in your network of interest.

### Initial Setup:

1. **Project Preparation:**

   If you have the project in a `.zip` file, first unzip it in your preferred directory 📂.

2. **Navigate to the Project Folder:**

   Open a terminal and change to the project directory, typically named `#3 Application of PageRank Algorithm`.

   ```
   cd /your/path/to/#3 Application of PageRank Algorithm
   ```

3. **Compilation:**

   Compile the source code with GCC, assigning a name of your choice to the executable. For example, if you want to name it `pagerank_analyzer`, use the following command:

   ```
   gcc -o pagerank_analyzer main.c src/*
   ```

### Execution:

With the project compiled, you are ready to run the program and explore the relationships in your specific network.

```
./<executable name> <alpha> <epsilon> <graph_file>
```

Replace `<executable name>`, `<alpha>`, `<epsilon>`, and `<graph_file>` with the appropriate values for your analysis.

#### Examples of Graph Files:

- `data/group_1(graph).txt`
- `data/group_1(matrix).txt`
- `data/group_2(graph).txt`
- `data/group_2(matrix).txt`
- `data/group_3(graph).txt`
- `data/group_3(matrix).txt`
- `data/reference_graph.txt`

These files symbolize different networks that you can analyze 🕵️‍♂️, adjusting the parameters `<alpha>` and `<epsilon>` according to your specific needs.

### Example of Use:

```
./pagerank_analyzer 0.85 0.01 data/group_2(matrix).txt
```

This command starts the analysis of the network defined in `group_2(matrix).txt`, using an `alpha` of 0.85 and an `epsilon` of 0.01, adapting to a wide range of applications and providing valuable insights into the relationships within the analyzed network 📊.

---

We are excited about the possibility of you using this project to discover and analyze the complex interactions in your networks of interest 🌟. Whether it's to improve the understanding of social structures, optimize SEO strategies, or any other use case, this project is designed to provide a deep and detailed understanding of the relationships and the relative importance of nodes within a network 🚀.