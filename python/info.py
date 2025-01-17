

def StringPainter(color, string):  # Transforms a string in a colored one;
    if color == "blue":
        special_opener = "\033[94m"
        special_closer = "\033[0m"
    if color == "orange":
        special_opener = "\033[36m"
        special_closer = "\033[0m"
    elif ():
        print("Color unavailable...")
    painted_string = special_opener + string + special_closer
    return painted_string


guide = "..."

questions_list = ""

questions = [  # raws questions: pure strings;
    "How to perform a Backpropagation?",
    "How to add an hidden layer?",
    "What does hidden_layer class take in input?",
    "How to perform a Random Training?",
    "Which activatiion functions are available?",
    "Which loss functions are available? ",
]

answers = [  # answers;
    f"After passing {StringPainter('blue', 'true')} to the last hidden, call the method with -your_last_hidden_name-\033[94m.Backpropagation()\033[0m.",
    f"Test for {StringPainter('orange', 'painter')}",
    f"Hidden_layer class takes 3 arugments: a {StringPainter('blue', 'string')} (in lowercase format) corresponding to the layer's activation function (currently are available linear, relu and sigmoid), "
    + f"an {StringPainter('blue', 'int')} (depth) equal to the hidden layer's number and a {StringPainter('blue', 'bool')} (setted to false by default) to indicate if it's the output layer.",
    f"After passing {StringPainter('blue', 'true')} to the last hidden, call the method with -your_last_hidden_name-\033[94m.RandomTraining()\033[0m.",
    f"You can choose between: \n • linear \n • relu \n • sigmoid \n • threshold",
    "For now are available \n • MSE (mean square error) \n • BCE (binary cross entropy)",
]
