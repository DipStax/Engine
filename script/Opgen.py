from itertools import chain

class_name = 'Property<T>'
value_name = 'm_value'

definition = False
implem = False
concept = True

# Printer

comp_op = [ '==', '!=', '<', '>', '<=', '>=', '<=>' ]
comp_op_name = [ 'EqOp', 'NEqOp', 'LsOp', 'GtOp', 'LsEqOp', 'GtEqOp', 'GlobCompOp' ]

arith_op = [ '+', '-', '*', '/', '%', '&', '|', '^', '<<', '>>' ]
assign_op = [ '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>=' ]
arith_op_name = [ 'AddOp', 'SubOp', 'MulOp', 'DivOp', 'ModOp', 'BitAndOp', 'BitOrOp', 'BitXorOp', 'LShiftOp', 'RShiftOp' ]

if concept:
    for [ op_sign, op_name ] in zip(comp_op, comp_op_name):
        print('template<class T, class _T>')
        print(f'concept {op_name} = requires (T r, _T l)')
        print('{')
        print(f'    r {op_sign} l;')
        print('};')
        print()

    for [ op_sign, op_name ] in zip(arith_op, arith_op_name):
        print('template<class T, class _T>')
        print(f'concept {op_name} = requires (T r, _T l)')
        print('{')
        print(f'    r {op_sign} l;')
        print('};')
        print()

    for [ op_sign, op_name ] in zip(assign_op, arith_op_name):
        print('template<class T, class _T>')
        print(f'concept Assign{op_name} = requires (T r, _T l)')
        print('{')
        print(f'    r {op_sign} l;')
        print('};')
        print()

    for op_sign, op_name in zip([ '++', '--' ], [ 'IncOp', 'DecOp' ]):
        print('template<class T>')
        print(f'concept Pre{op_name} = requires (T r)')
        print('{')
        print(f'    r{op_sign};')
        print('};')
        print()
        print('template<class T>')
        print(f'concept Post{op_name} = requires (T r)')
        print('{')
        print(f'    {op_sign}r;')
        print('};')
        print()

for [ op_sign, op_name ] in zip(comp_op, comp_op_name):
    if definition:
        print(f'template<{op_name}<T> _T>')
        print(f'[[nodiscard]] bool operator{op_sign}(const _T &_val) const;')

        print()

    if implem:
        print(f'template<class T>')
        print(f'template<{op_name}<T> _T>')
        print(f'bool {class_name}::operator{op_sign}(const _T &_val) const')
        print('{')
        print(f'    return {value_name} {op_sign} _val;')
        print('}')

        print()

for op_sign, op_name in zip(arith_op, arith_op_name):
    if definition:
        print(f'template<{op_name}<T> _T>')
        print(f'[[nodiscard]] T operator{op_sign}(const _T &_val) const;')

        print()

    if implem:
        print(f'template<class T>')
        print(f'template<{op_name}<T> _T>')
        print(f'T {class_name}::operator{op_sign}(const _T &_val) const')
        print('{')
        print(f'    return {value_name} {op_sign} _val;')
        print('}')

        print()

for op_sign, op_name in zip(assign_op, arith_op_name):
    if definition:
        print(f'template<Assign{op_name}<T> _T>')
        print(f'{class_name} operator{op_sign}(const _T &_val);')

        print()

    if implem:
        print(f'template<class T>')
        print(f'template<Assign{op_name}<T> _T>')
        print(f'{class_name} {class_name}::operator{op_sign}(const _T &_val)')
        print('{')
        print(f'    {value_name} {op_sign} _val;')
        print(f'    return *this;')
        print('}')

        print()

for op_sign, op_name in zip([ '++', '--' ], [ 'IncOp', 'DecOp' ]):
    if definition:
        print(f'requires Pre{op_name}<T>')
        print(f'T operator{op_sign}();')

        print()

    if implem:
        print(f'template<class T>')
        print(f'requires Pre{op_name}<T>')
        print(f'{class_name} {class_name}::operator{op_sign}()')
        print('{')
        print(f'    {value_name}{op_sign};')
        print(f'    return *this;')
        print('}')

        print()

    if definition:
        print(f'requires Post{op_name}<T>')
        print(f'{class_name} operator{op_sign}(int);')

        print()

    if implem:
        print(f'template<class T>')
        print(f'requires Post{op_name}<T>')
        print(f'{class_name} {class_name}::operator{op_sign}(int)')
        print('{')
        print(f'    {op_sign}{value_name};')
        print(f'    return *this;')
        print('}')

        print()