import argparse

def main(description_file, oprt_class_name, base_class_name):
    namelist = oprt_class_name.split('_')
    filename = ""
    classname = ""
    for name in namelist:
        name = name.lower()
        if len(name) > 0:
            classname += name[0].upper() + name[1:]
            filename += name
    
    header_file = filename + ".h"
    cpp_file = filename + ".cpp"
    
    with open(description_file, "r") as file:
        ft = {}
        for line in file:
            line = line.strip()

            type_name, fields = line.split(':')
            type_name = type_name.strip()
            fields = fields.strip()
            
            ft[type_name] = fields
            
    with open(f"src/include/{header_file}", "w") as file:
        print("#pragma once", file=file)
        print("#include \"expr.h\"", file=file)
        print("#include \"token.h\"", file=file)
        print("#include \"allexpr.h\"", file=file)
        print("", file=file)   
    
        print(f"class {classname} : public Oprt " + "{", file=file)
        print("    public:", file=file)
        
        for type, _ in ft.items():
            print(f"        Object oprt{type}({type}* {base_class_name.lower()}) override;", file=file)
            print("", file=file)    
            
        print("};", file=file)  
            
    with open(f"src/{cpp_file}", "w") as file:
        print(f"#include \"include/expr.h\"", file=file)
        print(f"#include \"include/oprt.h\"", file=file)
        print(f"#include \"include/allexpr.h\"", file=file)
        print(f"#include \"include/{header_file}\"", file=file)
        
        print("", file=file)

        for type, _ in ft.items():
            print(f"Object {classname}::oprt{type}({type}* {base_class_name.lower()}) " + "{}", file=file)
            print("", file=file)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("description_file")
    parser.add_argument("oprt_class_name")
    parser.add_argument("base_class_name")
    
    args = parser.parse_args()
    
    # running command from root directory -> python3 src/tools/genoprt.py src/tools/expr_description.txt ast_printer Expr
    main(args.description_file, args.oprt_class_name, args.base_class_name)