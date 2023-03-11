import numpy as np
import pandas as pd
from parglare import Parser, Grammar


def table_entry(value):
    value = value.split(':')
    if value[0][1] == 'A':
        return "acc"
    return value[0][1].lower() + value[1].replace(']', '')


if __name__ == "__main__":

    grammar = r"""
    E: E '+' T | T;
    T: T '*' F | F;
    F: '(' E ')' | id;
    
    terminals
    id: /id/;
    """

    g = Grammar.from_string(grammar)

    parser = Parser(g)

    table = parser.table

    n_states = len(table.states)
    non_terminals = " ".join(g.nonterminals.keys()).replace("S'", '')
    terminals = " ".join(g.terminals.keys())

    print('-' * 20 + " LR Table " + '-' * 20)
    print(f"- Number of states:\t{n_states}")
    print("- Terminal symbols:\t" + terminals)
    print("- Nonterminal symbols:\t" + non_terminals)
    print('-' * 50)

    df = pd.DataFrame(
        index=range(n_states), columns=(terminals + ' ' + non_terminals).split(" ")
    )

    for i, state in enumerate(table.states):

        for symbol, action in state.actions.items():
            df.at[i, str(symbol)] = table_entry(str(action))

        for symbol, go in state.gotos.items():
            df.at[i, str(symbol)] = str(go.state_id)

    df = df.fillna('')

    print(df)

    df.to_csv('lr_table.csv', sep='\t', index=True)
