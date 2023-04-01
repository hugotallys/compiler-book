import pandas as pd

from csnake import CodeWriter, Enum
from parglare import Parser, Grammar


def table_entry(value):
    value = value.split(':')
    if value[0][1] == 'A':
        return "acc"
    return value[0][1].lower() + value[1].replace(']', '')


def get_action_table_row(row):
    return [get_action_table_entry(r) for r in row]


action2int = {
    'SHIFT': 0,
    'REDUCE': 1,
    'ACCEPT': 2,
    'ERROR': 3
}


def get_action_table_entry(action_value):
    if action_value == '':
        return {'action': action2int['ERROR'], 'id': 0}
    elif action_value == 'acc':
        return {'action': action2int['ACCEPT'], 'id': 0}
    elif action_value[0] == 's':
        return {'action': action2int['SHIFT'], 'id': action_value[1:]}
    elif action_value[0] == 'r':
        return {'action': action2int['REDUCE'], 'id': action_value[1:]}


if __name__ == "__main__":

    with open('grammar.pg', 'r') as file:
        grammar = file.read()

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
    # df = df.drop(columns=['EMPTY'])
    # terminals = terminals.replace(' EMPTY ', ' ')

    print(df)

    cw = CodeWriter()

    # include stdio.h and stdlib.h
    cw.include("<stdio.h>")
    cw.include("<stdlib.h>")

    cw.add_line('')

    # define the number of states and productions
    cw.add_define('N_STATES', n_states)
    cw.add_define('N_PRODUCTIONS', len(prods) - 1)

    # enum for terminals
    terminals_enum = Enum('Terminal', typedef=True)

    for terminal in terminals.split(' '):
        terminals_enum.add_value(terminal)

    terminals_enum.add_value("TERMINAL_SIZE")

    cw.add_line('')

    cw.add_enum(terminals_enum)

    # enum for nonterminals
    nonterminals_enum = Enum('NonTerminal', typedef=True)

    nt2int = {}

    for i, nonterminal in enumerate(non_terminals.strip(' ').split(' ')):
        nonterminals_enum.add_value(nonterminal)
        nt2int[nonterminal] = i

    nonterminals_enum.add_value("NON_TERMINAL_SIZE")
    nt2int["NON_TERMINAL_SIZE"] = len(non_terminals.strip(' ').split(' '))

    cw.add_line('')

    cw.add_enum(nonterminals_enum)

    production_array = [
        (nt2int[str(p.symbol)], len(p.rhs)) for p in prods[1:]
    ]

    with open('productions.txt', 'w') as file:
        for p in production_array:
            file.write(f"{p[0]} {p[1]}\n")

    cw.add_line('')

    # define the action table
    action_table = df[terminals.split(' ')].to_numpy()

    with open('action_table.txt', 'w') as file:
        for i, row in enumerate(action_table):
            for j, entry in enumerate(row):
                action, id_ = get_action_table_entry(entry).values()
                file.write(f"{action} {id_}\n")

    cw.add_line('')

    # define the goto table
    goto_table = df[non_terminals.strip(' ').split(' ')].replace('', 0).to_numpy()

    with open('goto_table.txt', 'w') as file:
        for i, row in enumerate(goto_table):
            for j, entry in enumerate(row):
                file.write(f"{entry}\n")

    cw.write_to_file('output.c')
