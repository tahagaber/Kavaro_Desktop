with open("d:/Kavaro_decktop/src/main.cpp", "r", encoding="utf-8") as f:
    lines = f.readlines()
with open("d:/Kavaro_decktop/src/FinancialDashboard.h", "w", encoding="utf-8") as f:
    f.write("#pragma once\n")
    f.writelines(lines[2:835])
with open("d:/Kavaro_decktop/src/main.cpp", "w", encoding="utf-8") as f:
    f.writelines(lines[:2])
    f.write("#include \"FinancialDashboard.h\"\n")
    f.writelines(lines[835:])
