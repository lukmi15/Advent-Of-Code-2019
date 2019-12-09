with open(r'input1.txt', 'r') as f:
    raw_input = f.read().strip().split('\n')

def fuel_required(weight):
    return max((weight // 3) - 2, 0)

print("Day One:", sum([fuel_required(int(x)) for x in raw_input]))

def fuel_extra_weight(weight):
    fuel_req = max((weight // 3) - 2, 0)
    if fuel_req == 0: return 0
    return fuel_req + fuel_extra_weight(fuel_req)

print("Day Two:", sum([fuel_extra_weight(int(x)) for x in raw_input]))
