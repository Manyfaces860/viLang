import argparse

def main(baseClass, descriptionFile, outputFile, operator_file, astFile):
    with open(descriptionFile, "r") as file:
        ft = {}
        for line in file:
            line = line.strip()

            type_name, fields = line.split('##')
            type_name = type_name.strip()
            fields = fields.strip()
            
            ft[type_name] = fields
        
    # creates base expression, statement class
    with open(astFile, "w") as file:
        print("#pragma once", file=file)
        print("#include \"token.h\"", file=file)
        
        if baseClass == "Expr":
            print(f"class Oprt;", file=file)
        else:
            print(f"class Oprt{baseClass};", file=file)
        
        print("", file=file)
        print(f"class {baseClass} " + "{", file=file)
        print(f"    public:", file=file)
        
        if baseClass == "Expr":
            print(f"        virtual Object accept(Oprt* oprt) = 0;", file=file)
        else: 
            print(f"        virtual Object accept(Oprt{baseClass}* oprt) = 0;", file=file)
            
        print(f"        virtual ~{baseClass}() noexcept(false) = default;", file=file)
        print("};", file=file)
        
    # creates concreate implementations of base class
    with open(outputFile, "w") as file:
        print("#pragma once", file=file)
        print("#include <vector>", file=file)
        print(f"#include \"{baseClass.lower()}.h\"", file=file)
        print("#include \"token.h\"", file=file)
        if baseClass == "Expr":
            print(f"#include \"oprt.h\"", file=file)
        else:
            print(f"#include \"oprt{baseClass.lower()}.h\"", file=file)

        print("using std::vector;", file=file)
        print("", file=file)
        
        for type, field in ft.items():
            write_class(file, type, field, baseClass)
            
    # creates base operator(visitor) class
    with open(operator_file, "w") as file:
        print("#pragma once", file=file)
        print("#include \"token.h\"", file=file)
        print("", file=file)    
        
        for type, field in ft.items():
            print(f"class {type};", file=file)
            
        print("", file=file)
        
        if baseClass == "Expr":
            print(f"class Oprt " + "{", file=file)
        else:
            print(f"class Oprt{baseClass} "+"{", file=file)
            
        print("    public:", file=file)
        
        for type, field in ft.items():
            print(f"        virtual Object oprt{type}({type}* {baseClass.lower()}) = 0;", file=file)
        
        if baseClass == "Expr":
            print(f"        virtual ~Oprt() noexcept(false) = default;", file=file)
        else:
            print(f"        virtual ~Oprt{baseClass}() noexcept(false) = default;", file=file)
            
        print("};", file=file)
        print("", file=file)
    
    
def write_class(file, type, field: str, baseClass):
    
    print(f"class {type} : public {baseClass} " + '{', file=file)
    print("    public:", file=file)
    
    member_init = ""
    last = len(field.split("|| "))-1

    for i, f in enumerate(field.split("|| ")):
        print(f"        {f};", file=file)
        _, name = f.split(" ")
        if i == last:
            member_init += f"{name}({name})"
        else:
            member_init += f"{name}({name}), "
        
    print("", file=file)
    print(f"        {type}({field.replace('|| ', ', ')}) : {member_init} " + "{}", file=file)
    if baseClass == "Expr":
        print(f"        Object accept(Oprt* oprt) override " + "{", file=file)
    else:
        print(f"        Object accept(Oprt{baseClass}* oprt) override " + "{", file=file)
    
    print(f"            return oprt->oprt{type}(this);", file=file)
    print("        }", file=file)
    print("};", file=file)
    print("", file=file)

    


    
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("base_class_name")
    parser.add_argument("description_file")
    parser.add_argument("output_file")
    parser.add_argument("operator_file")
    parser.add_argument("astFile")
    
    args = parser.parse_args()
    
    # running command python3 src/tools/genast.py Expr src/tools/expr_description.txt src/include/allexpr.h src/include/oprt.h
    main(args.base_class_name, args.description_file, args.output_file, args.operator_file, args.astFile)