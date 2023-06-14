import pdb

# Function to take input for 3x3 array
def take_input():
    array = []
    for i in range(3):
        row = input(f"Enter elements for row {i + 1} (separated by space): ").split()
        array.append(row[::-1])
    return array

# Function to print the 3x3 array
def print_storage(array):
    for i in range(len(array)):
        for j in range(len(array[i])-1, -1, -1):
            print(array[i][j], end=" ")
        print()

def print_values(loaded_values):
    for i in range(len(loaded_values)):
        print(loaded_values[i], end=" ")
        if((i+1)%3 == 0):
           print()
    if((i+1)%3 !=0):
        print()

# Main program
print("Enter elements for a 3x3 HBW storage:")
array = take_input()

print("\nEntered HBW storage:")
print_storage(array)


def update_storage(updated_values, wp):
    n = len(updated_values)
    count = 1
    panic = False
    update = False
    for i in range(3):
        for j in range(2,-1,-1):
            #print(i,j)
            if count == n:
                #print(i,j,count, n, array[i][j])
                #print(type(array[i][j]), type(wp))
                if int(array[i][j]) == wp:
                    print("PANIC => wp:", wp, "== storage[i][j]:",array[i][j])    
                    print()
                    panic = True
                    break;
                if int(updated_values[-1]) != 0 and wp == 1:
                    print("PANIC => The position contains a workpiece.")
                    print()
                    panic = True
                    break

                array[i][j] = wp 
                update = True
                break
            count += 1
        if panic or update:
            break
    print("Updated storage:")
    print_storage(array)
    if wp == 0 and not panic:
        print("Removed workpiece from this position i,j:",i,j)
    elif wp == 1 and not panic:
        print("Stored workpiece at this position i,j:", i,j)
 
def extract_loaded_values_2nd_part(file_content):
    loaded_values = []
    total_load = 0
    remove = False
    store = False
    found_nextPosition = False

    #for line in file_content:
    for i in range(len(file_content)):
        line = file_content[i]
        if "TxtHighBayWarehouseStorage5fetch" in line and "Function" in line:
            print()
            print("Ordered function found: ", line.split()[-1])
            time = file_content[i-1]
            remove = True
            store = False
        if "TxtHighBayWarehouseStorage14fetchContainer" in line and "Function" in line:
            print()
            print("Storing function found: ", line.split()[-1])
            time = file_content[i-1]
            store = True
            remove = False

        if "loaded values" in line and (remove or store):
            loaded_value = line.split()[-1] 
            loaded_values.append(loaded_value)
            ##print(line)            
            #if loaded_value != "-1":
            #    loaded_values.append(loaded_value)
            #    total_load += 1
            #if int(loaded_value) == 0 and store:
            #    found_nextPosition = True
            #    store = False
            ##print(total_load)
        
        if "TxtHighBayWarehouseStorage10isValidPosENS_11StoragePos" in line and (remove or store):
            print("Loaded values:",loaded_values)
            print("At this unix time: ", time.split()[-1])
            pos1 = loaded_values[-2]
            pos2 = loaded_values[-1]
            loaded_values = loaded_values[:-2] ## removed the last 2 values of position
            if pos1 == '-1' or pos2 == '-1':
                print("No space left on device.\nPos1,pos2:",pos1,pos2)
            elif remove:
                #pos1 = loaded_values[-2]
                #pos2 = loaded_values[-1]
                #loaded_values = loaded_values[:-2] ## removed the last 2 values of position
                #loaded_values = loaded_values[1::2] ## sliced the list starting from index 1 with a step of size 2, as there is 2 conditions
                loaded_values = [value for value in loaded_values if value in ['0', '1', '2', '3']]
                print("types loaded: ")
                print_values(loaded_values)
                print("Removing wp from this postion: ",pos1,pos2)
                update_storage(loaded_values, 0)
            elif store or found_nextPosition:
                #pos1 = loaded_values[-2]
                #pos2 = loaded_values[-1]
                #loaded_values = loaded_values[:-2] ## removed the last 2 values of position
                print("Storing wp at this position: ", pos1, pos2)
                update_storage(loaded_values, 1)

            #print("Values loaded: ")
            #for i in range(len(loaded_values)):
            #    print(loaded_values[i], end=" ")
            #    if((i+1)%3 == 0):
            #        print()
            #print("At this unix time: ", time.split()[-1])
            #print("Total loaded:",total_load)
            loaded_values = []
            total_load = 0
            store = False
            found_nextPosition = False
            remove = False
            #break
    return loaded_values


def process_file(file_name):
    with open(file_name, "r") as file:
        file_content = file.readlines()
        updated_storage = extract_loaded_values_2nd_part(file_content)
        return updated_storage 

## 2nd part
#storage = process_file("checking_positions.txt")
storage = process_file("test-combined.txt")
#storage = process_file("t2.txt")
#storage = process_file("hbw-mfetch.txt")
#storage = process_file("hbw-mstore.txt")
#storage = process_file("../../5.multi-fetch-storage/4.Combined/combined.txt")

## 1st part
#stored = process_file("test1p.txt")

#print("Loaded values from 2nd-part checking_positions.txt:")
#print(storage)
