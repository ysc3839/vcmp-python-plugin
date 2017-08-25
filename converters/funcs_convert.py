from name_convert import convert_name
from args_list import get_args_list
import re

regex = r'\/\*(.+)\*\/\n\s*(\S+) \(\*([^)]+)\) \(([^)]+)\);'

f = open('funcs.txt', 'r')
matches = re.finditer(regex, f.read(), re.MULTILINE)
f.close()

f = open('funcs.conv.txt', 'w', newline='\n')
for match in matches:
    doc = match.group(1).strip()
    ret_type = match.group(2)
    func_name = match.group(3)
    args_list_str = match.group(4)
    if args_list_str == 'void': args_list_str = ''
    args_list = get_args_list(args_list_str)
    conv_func_name = convert_name(func_name)
    args_name = ''
    if args_list:
        args_name = ', '.join([n[1] for n in args_list])
        #print(args_name)

    is_return = 'return '
    if ret_type == 'void':
        is_return = ''

    string = r'''functions.def("{conv_func_name}", []({args_list_str}) {{
    {is_return}vcmpFunctions->{func_name}({args_name});
}});
'''.format(**locals())

    print("%s %s %s %s" % (doc, ret_type, func_name, args_list))
    f.write(string)

f.close()
