def get_args_list(liststr):
    if not liststr or liststr == 'void': return None
    args = liststr.split(',')
    args_list = []
    for arg in args:
        arg = arg.strip()
        if arg == '...':
            args_list.append(('', '...'))
            continue
        arg_type, name = arg.rsplit(' ', 1)
        args_list.append((arg_type, name))
    return args_list
