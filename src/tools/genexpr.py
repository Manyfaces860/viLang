import argparse

def main(baseClass, descriptionFile, outputFile, operator_file):
    with open(descriptionFile, "r") as file:
        ft = {}
        for line in file:
            line = line.strip()

            type_name, fields = line.split(':')
            type_name = type_name.strip()
            fields = fields.strip()
            
            ft[type_name] = fields
        
    with open(outputFile, "w") as file:
        print("#pragma once", file=file)        
        print("#include \"expr.h\"", file=file)
        print("#include \"token.h\"", file=file)
        print("", file=file)
        
        for type, field in ft.items():
            write_class(file, type, field, baseClass)
            
    with open(operator_file, "w") as file:
        print("#pragma once", file=file)
        print("#include \"expr.h\"", file=file)
        print("", file=file)    
        
        for type, field in ft.items():
            print(f"template <typename T> class {type};", file=file)
        
        print("template <typename T>", file=file)
        print("class Oprt {", file=file)
        print("    public:", file=file)
        
        for type, field in ft.items():
            print(f"        virtual T oprt{type}({type}<T>* expr) = 0;", file=file)
            
        print(f"        virtual ~Oprt() noexcept(false) = default;", file=file)
        print("};", file=file)
        print("", file=file)
    
    
def write_class(file, type, field: str, baseClass):
    
    print("template <typename T>", file=file)
    print(f"class {type} : public {baseClass}<T> " + '{', file=file)
    print("    public:", file=file)
    
    member_init = ""
    last = len(field.split(", "))-1

    for i, f in enumerate(field.split(", ")):
        print(f"        {f};", file=file)
        _, name = f.split(" ")
        if i == last:
            member_init += f"{name}({name})"
        else:
            member_init += f"{name}({name}), "
        
    print("", file=file)
    print(f"        {type}({field}) : {member_init} " + "{}", file=file)
    print("        T accept(Oprt<T>* oprt) override {", file=file)
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
    
    args = parser.parse_args()
    
    # running command python3 src/tools/genexpr.py Expr src/tools/expr_description.txt src/include/allexpr.h src/include/oprt.h
    main(args.base_class_name, args.description_file, args.output_file, args.operator_file)