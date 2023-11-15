import xmltodict, json
import re

pattern = r'\b(\d+),(\d+)\b'

filePath = 'f1_general.plist'

with open(filePath) as f:
    lines = f.read()
    o = xmltodict.parse(lines)
    
    keys = o["plist"]["dict"]["dict"][0]["key"]
    frames = o["plist"]["dict"]["dict"][0]["dict"]
    lastDimensions = 0
    dico = {}
    for key,frame in zip(keys,frames):
        print(key) # make sure they are sorted
        keyName = key.split("_")[2]
        if (not keyName in {"attack","breathing","cast","castend","castloop","caststart","death","hit","idle","run","cast"}):
            print(f"{keyName} not recognised as a key")
        if not keyName in dico :
            dico[keyName] = []

        position = frame["string"][0]
        size = frame["string"][2]
        matches = re.findall(pattern, position)
        coord = matches[0]
        dimension = matches[1]

        if (lastDimensions == 0):
               lastDimensions = dimension
               print(f"Initial dimension found: {dimension}")
        elif(dimension != lastDimensions):
            print(f"New dimension found: {dimension}")

        x = tuple(coord)[0]
        y = tuple(coord)[1]
        dico[keyName].append({"x":x,"y":y})

    print(size)
    width = tuple(size)[0]
    height = tuple(size)[1]
    finalDico = {
        "frameWidth": width,
        "frameHeight": height,
        "frameDuration": 100,
        "lists": dico
    }
    filePath = filePath.replace(".plist",".plist.json")
    out_file = open(filePath, "w")
    json.dump(finalDico, out_file, indent = 6)

