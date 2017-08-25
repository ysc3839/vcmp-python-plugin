from name_convert import convert_name
from args_list import get_args_list
import re

regex = r'(\S+) \(\*([^)]+)\) \(([^)]+)\);'

f = open('calls.txt', 'r')
matches = re.finditer(regex, f.read(), re.MULTILINE)
f.close()

func_names = []

f = open('calls.conv.txt', 'w', newline='\n')
for match in matches:
    ret_type = match.group(1)
    func_name = match.group(2)
    args_list_str = match.group(3)
    if args_list_str == 'void': args_list_str = ''
    args_list = get_args_list(args_list_str)
    conv_func_name = convert_name(func_name)
    args_name = ''

    if args_list:
        args_name = ', '.join([n[1] for n in args_list])
        print(args_name)

    string = r'''{ret_type} {func_name}({args_list_str})
{{
	try
	{{
		if (moduleCallbacks)
		{{
			auto func = moduleCallbacks->attr("{conv_func_name}");
			if (py::isinstance<py::function>(func))
				func.call({args_name});
		}}
	}}
	catch (...)
	{{
		PythonExceptionHandler();
	}}
}}

'''.format(**locals())

    #string = "callbacks->{func_name} = {func_name};\n".format(**locals())

    f.write(string)

f.close()
