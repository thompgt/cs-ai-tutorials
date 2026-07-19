# CS & AI Tutorials

A growing, in-depth collection of tutorials on computer science, data science,
and AI/ML concepts — each one combining **theory**, **visuals**,
**implementation**, and **real-world use cases** in a single place.

The goal: for any concept, you should be able to find one tutorial that takes
you from "what is this and why does it matter" through the math, a working
implementation, and a look at how it's actually used in practice.

## How tutorials are organized

Tutorials live under topic domains at the repo root. Each tutorial is its own
folder containing a self-contained notebook and/or report:

```
<domain>/<tutorial-name>/
├── README.md            # summary, prerequisites, learning objectives
├── tutorial.ipynb        # theory + visuals + implementation, or
├── report.md              # long-form writeup for math-heavy topics, and/or
└── src/                    # supporting code, if the notebook outgrows inline cells
```

See [`_template/`](_template) for the scaffold used to start a new tutorial,
and [`CONTRIBUTING.md`](CONTRIBUTING.md) for the full writing guide.

## Domains

| Domain | Description |
|---|---|
| [`math-and-statistics`](math-and-statistics) | Linear algebra, probability, calculus, statistical inference |
| [`data-structures-algorithms`](data-structures-algorithms) | Core CS: trees, graphs, sorting, complexity analysis |
| [`software-engineering`](software-engineering) | Design patterns, testing, architecture, code quality |
| [`systems`](systems) | Operating systems, networking, distributed systems, concurrency |
| [`databases`](databases) | Relational/NoSQL design, indexing, query optimization, transactions |
| [`big-data`](big-data) | Distributed processing, Spark, streaming, data lakes |
| [`data-engineering`](data-engineering) | Pipelines, ETL/ELT, orchestration, data modeling |
| [`devops`](devops) | CI/CD, containers, infrastructure as code, observability |
| [`machine-learning`](machine-learning) | Classical ML: regression, trees, SVMs, clustering, gradient descent |
| [`deep-learning`](deep-learning) | Neural nets, CNNs, RNNs, transformers, attention |
| [`generative-ai`](generative-ai) | LLMs, diffusion models, RAG, agents, prompting |
| [`nlp`](nlp) | Text processing, embeddings, language modeling |
| [`time-series`](time-series) | Forecasting, seasonality, state-space models |
| [`causal-inference`](causal-inference) | Experiment design, causal graphs, treatment effect estimation |
| [`responsible-data-science`](responsible-data-science) | Fairness, privacy, interpretability, ethics |

## Running the notebooks

```bash
git clone https://github.com/thompgt/cs-ai-tutorials.git
cd cs-ai-tutorials
conda env create -f environment.yml
conda activate cs-ai-tutorials
jupyter lab
```

## Contributing

New tutorials, fixes, and topic requests are welcome — see
[`CONTRIBUTING.md`](CONTRIBUTING.md) to get started.

## License

Code is licensed under [MIT](LICENSE). Written content (reports, notebook
markdown, images) is licensed under
[CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).
