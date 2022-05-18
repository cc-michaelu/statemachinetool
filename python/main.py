import os
import re

BEGIN_RE = re.compile(r'digraph\s+(\w+)\s+{')
NODE_RE = re.compile(r'node\s+\[([\w,=]+)\]\s+(\w+)')
CONNECT_RE = re.compile(r'(\w+)\s+\-\>\s(\w+)\s+\[([\w=",]+)\]')


class StateNode:
    name = ""
    attrs = {}

    def __init__(self, name: str, attr: str):
        self.name = name
        attr_list = attr.split(',')
        for attr in attr_list:
            attribute_name, attribute_value = attr.split('=')
            self.attrs[attribute_name] = attribute_value

    def __repr__(self):
        return f'({self.name} w/{len(self.attrs)} attributes)'


class StateEdge:
    state_1 = ''
    state_2 = ''
    attrs = {}

    def __init__(self, state_1: str, state_2: str, attr: str):
        self.state_1 = state_1
        self.state_2 = state_2
        attr_list = attr.split(',')
        for attr in attr_list:
            attribute_name, attribute_value = attr.split('=')
            self.attrs[attribute_name] = attribute_value

    def __repr__(self):
        return f'(State {self.state_1} transition to {self.state_2})'


class StateMachine:

    node_list = []
    edge_list = []
    machine_name = ''

    def __init__(self, filename: str):
        self.machine_name, self.node_list, self.edge_list = StateMachine.parse_statemachine_dot(filename)
        pass

    def __repr__(self):
        return f'{self.node_list},\n{self.edge_list}'

    @staticmethod
    def parse_statemachine_dot(filename: str) -> tuple:
        """
        Load DOT file into nodes and edges...

        :param filename:
        :return:
        """
        node_list = []
        edge_list = []
        machine_name = ''

        try:
            with open(filename, 'r') as sm:
                line = sm.readline().strip()
                if line:
                    matches = BEGIN_RE.match(line)
                    if matches:
                        machine_name = matches[1]
                        # print('Found statemachine "{}"'.format(machine_name))

                        while True:
                            line = sm.readline()
                            if not line:
                                break
                            line = line.strip()

                            matches = NODE_RE.match(line)

                            if matches:
                                node_attributes = matches[1]
                                node_name = matches[2]
                                # print(f'Found {node_name} with attributes {node_attributes}')
                                node_list.append(StateNode(node_name, node_attributes))
                                continue

                            matches = CONNECT_RE.match(line)

                            if matches:
                                state_1 = matches[1]
                                state_2 = matches[2]
                                attributes = matches[3]

                                # print(f'Found transition from \"{state_1}\" to \"{state_2}\"')

                                edge_list.append(StateEdge(state_1, state_2, attributes))
                                continue

                            # print(line)
                    else:
                        print('Not a state machine graph')
        except FileNotFoundError:
            print('Statemachine DOT file not found')

        return machine_name, node_list, edge_list


def main():
    # nodes = parse_statemachine_dot('state-machine.dot')
    # print(nodes)
    machine = StateMachine('state-machine.dot')
    print(machine.node_list)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
