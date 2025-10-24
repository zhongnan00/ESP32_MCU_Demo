#!/usr/bin/env python3
import sys

config_file = sys.argv[1]
header_file = sys.argv[2]

with open(config_file) as f:
    lines = f.readlines()

with open(header_file, "w") as f:
    f.write("#ifndef CONFIG_H\n#define CONFIG_H\n\n")
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("CONFIG_"):
            name, value = line.split("=", 1)
            if value == "y":
                f.write(f"#define {name} 1\n")
            elif value == "n":
                f.write(f"/* {name} disabled */\n")
            elif value.startswith('"') and value.endswith('"'):
                f.write(f"#define {name} {value}\n")
            else:
                f.write(f"#define {name} {value}\n")
    f.write("\n#endif // CONFIG_H\n")
