import numpy as np
import re
import pandas as pd
from parglare import Parser, Grammar


def table_entry(value):
    value = value.split(':')
    if value[0][1] == 'A':
        return "acc"
    return value[0][1].lower() + value[1].replace(']', '')


if __name__ == "__main__":

    with open('grammar.txt', 'r') as file:
        grammar = file.read()

    # re to capture any text beetween %{ and %} and store under patterns
    patterns = re.findall(r"%\{(.+?)%\}", grammar, re.DOTALL)[0].strip('\n').strip(' ')
    patterns = re.findall(r"/(.+?)/ ([a-zA-Z_]+)", patterns, re.DOTALL)

    grammar = re.sub(r"::=", ':', grammar)
    grammar = re.sub(r"[<>]", "", grammar)
    grammar = re.sub(r"\n\n", ";\n\n", grammar)

    # remove patterns from grammar
    grammar = re.sub(r"%\{(.+?)%\}", "", grammar, flags=re.DOTALL)

    for pattern, label in patterns:
        grammar = re.sub(pattern, "'" + label + "'", grammar)

    print(grammar)

    g = Grammar.from_string(grammar)

    prods = g.productions

    parser = Parser(g)

    table = parser.table

    n_states = len(table.states)
    non_terminals = " ".join(g.nonterminals.keys()).replace("S'", '')
    terminals = " ".join(g.terminals.keys())

    print('-' * 20 + " LR Parser - Shift Reduce Table " + '-' * 20)

    print(f"- Number of states:\t{n_states}")

    print("- Terminal symbols:\t" + terminals)

    print("- Nonterminal symbols:\t" + non_terminals)
    print('-' * 72)

    print("- Productions:")

    for prod in prods:
        print(prod)

    print('-' * 72)

    df = pd.DataFrame(
        index=range(n_states), columns=(terminals + ' ' + non_terminals).split(" ")
    )

    for i, state in enumerate(table.states):

        for symbol, action in state.actions.items():
            df.at[i, str(symbol)] = table_entry(str(action))

        for symbol, go in state.gotos.items():
            df.at[i, str(symbol)] = str(go.state_id)

    df = df.fillna('')

    # drops the EMPTY column
    df = df.drop(columns=['EMPTY'])

    print(df)
