"""
File: proj1.py
Author: Daniel Omolewa
Date:
Section: 42
E-mail: o24@umbc.edu
Description: This program functions as a baking simulator (baking sim for short).
             The player (the user) will go ot the grocery store and purchase
             ingredients for baking baguettes, macarons and croissants. If they
             fail to stay within their budget or fail to purchase, they lose.

             If they are successful at purchasing ingredients, then they are then
             returned to the kitchen where they choose what items to work on.
             They must begin the baguette dough before working on the macarons
             and croissants, and they must finish every other task before baking
             the baguettes.

"""
STARTING_FUNDS = 80.0

FLOUR_COST_PER_BAG = 2.5
EGGS_COST_PER_CRATE = 1.9
YEAST_COST_PER_BAG = 3.25
BUTTER_COST_PER_PACK = 1.25
MILK_COST_PER_JUG = 2.75

GALLONS_MILK_PER_JUG = 1.0
EGGS_PER_CRATE = 24.0
TBSP_BUTTER_PER_PACK = 64.0
CUPS_FLOUR_PER_BAG = 25.0
CUP_YEAST_PER_BAG = 6.0

FLOUR_REQUIRED = 48.0 + 112.5
EGGS_REQUIRED = 12.0 + 60.0
BUTTER_REQUIRED = 144.0
YEAST_REQUIRED = 39 + 50
MILK_REQUIRED = 18.0

CUPS_IN_GALLON = 16
TSP_IN_CUP = 48

INGREDIENTS = ["flour", "eggs", "yeast", "butter", "milk"]

NOTHING = "NOTHING"

#Simply greet the user and show them what they need to get
def greeting():
    print("Baker! You must buy the following with $" +str(STARTING_FUNDS)+":")
    print("")
    print("For 300 croissants:")
    print("  48 cups of flour")
    print("  12 eggs")
    print("  144 tbsp of butter")
    print("  39 tsp of yeast")
    print("  18 cups of milk")
    print("")
    print("For 300 macarons:")
    print("  60 eggs")
    print("")
    print("For 100 baguettes:")
    print("  112.5 cups of flour")
    print("  50 tsp of yeast")
    print("")

#Take in the list of purchased items and check if the total cost is within the
#budget. If the total cost is over the budget, then the player receives a message
#telling them that they have ran out of money and the function retruns True,
#which is passed through have_lost. The return value is changed from have_lost to
#True
def check_within_budget(items):
    item1_cost = items[0] * FLOUR_COST_PER_BAG   
    item2_cost = items[1] * EGGS_COST_PER_CRATE
    item3_cost = items[2] * YEAST_COST_PER_BAG
    item4_cost = items[3] * BUTTER_COST_PER_PACK 
    item5_cost = items[4] * MILK_COST_PER_JUG
    total_cost = item1_cost + item2_cost + item3_cost + item4_cost + item5_cost

    if STARTING_FUNDS - total_cost <= 0:
        print("You have run out of money!")
        return True

#Take in a list of the purchased items and check if enough ingredients has been
#bought. Items in the list are multiplied by the respective amount per packing
#unit and compared to the required amount. If enough ingredients are bought,
#then False is returned. If not enough ingredients are bought, the player
#receives a message reprimanding them as well as how much of each ingredient is
#missing. The return value is changed from have_lost to either True or False.
def check_items_enough(items):
    measured_items = []
    required_items = [FLOUR_REQUIRED, EGGS_REQUIRED, YEAST_REQUIRED, BUTTER_REQUIRED, MILK_REQUIRED]
    potential_diffs = []
    
    item1_measured = items[0] * CUPS_FLOUR_PER_BAG
    item2_measured = items[1] * EGGS_PER_CRATE
    item3_measured = items[2] * CUP_YEAST_PER_BAG * TSP_IN_CUP 
    item4_measured = items[3] * TBSP_BUTTER_PER_PACK
    item5_measured = items[4] * CUPS_IN_GALLON
    measured_items.append(item1_measured)
    measured_items.append(item2_measured)
    measured_items.append(item3_measured)
    measured_items.append(item4_measured)
    measured_items.append(item5_measured)

    potential_diff1 = FLOUR_REQUIRED - item1_measured
    potential_diff2 = EGGS_REQUIRED - item2_measured
    potential_diff3 = YEAST_REQUIRED - item3_measured
    potential_diff4 = BUTTER_REQUIRED - item4_measured
    potential_diff5 = MILK_REQUIRED - item5_measured
    potential_diffs.append(potential_diff1)
    potential_diffs.append(potential_diff2)
    potential_diffs.append(potential_diff3)
    potential_diffs.append(potential_diff4)
    potential_diffs.append(potential_diff5)
    
    packagings = ["cups", "eggs", "tsp", "tbsp", "cups"]
    
    have_enough = True
    for i in range(len(measured_items)):
        if measured_items[i] < required_items[i]:
            have_enough = False
            print("You didn't buy enough", INGREDIENTS[i], "We needed:", potential_diffs[i],"more",packagings[i])
    if have_enough == True:
        print("We have everything we need! Ready! Set! Bake!")
        return False
    elif have_enough == False:
        print("You did not buy enough ingredients to even begin baking. You are a failure of all sorts. Good day.")
        return True
        
#Welcome the player to the supermarket. Ask them what they would like to buy and
#how much they want to buy until they wish to stop. After each time they purchase
#an item, call check_within_budget to see if they have not gone over the budget.
#If the player has not yet gone over the budget, update the the amount of each
#ingredient according to their input. Once the player finishes shopping and they
#have not gone over the budget, check if they have enough ingredients through
#calling the function check_items_enough. The return value from
#check_items_enough is passed through here. If it's False, the player continues.
#If it's True, the player loses. The return value is changed from the ingredients
#to either True or False.
def go_shopping():
    print("Welcome to the supermarket!")
    num_egg_crates = 0
    num_flour_bags = 0
    num_butter_packs = 0
    num_yeast_bags = 0
    num_milk_jugs = 0
    
    item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ") 
    while item != NOTHING:
        if item not in INGREDIENTS:
            print("That is not a valid entry.")
            item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ")
        elif item == "eggs":
            num_egg_crates += float(input("How many crates of eggs would you like? "))
            bought_items = [num_flour_bags, num_egg_crates, num_yeast_bags, num_butter_packs, num_milk_jugs]
            check = check_within_budget(bought_items)
            if check == True:
                check_items_enough(bought_items)
                return True 
            item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ")
        elif item == "flour":
            num_flour_bags += float(input("How many bags of flour would you like? "))
            bought_items = [num_flour_bags, num_egg_crates, num_yeast_bags, num_butter_packs, num_milk_jugs]
            check = check_within_budget(bought_items)
            if check == True:
                check_items_enough(bought_items)
                return True
            item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ")
        elif item == "butter":
            num_butter_packs += float(input("How many packs of butter would you like? "))
            bought_items = [num_flour_bags, num_egg_crates, num_yeast_bags, num_butter_packs, num_milk_jugs]
            check = check_within_budget(bought_items)
            if check == True:
                check_items_enough(bought_items)
                return True 
            item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ")
        elif item == "yeast":
            num_yeast_bags += float(input("How many bags of would you like? "))
            bought_items = [num_flour_bags, num_egg_crates, num_yeast_bags, num_butter_packs, num_milk_jugs]
            check = check_within_budget(bought_items)
            if check == True:
                check_items_enough(bought_items)
                return True 
            item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ")
        elif item == "milk":
            num_milk_jugs += float(input("How many jugs of milk would you like? "))
            bought_items = [num_flour_bags, num_egg_crates, num_yeast_bags, num_butter_packs, num_milk_jugs]
            check = check_within_budget(bought_items)
            if check == True:
                check_items_enough(bought_items)
                return True 
            item = input("What would you like to purchase? (ENTER 'NOTHING' to leave store) ")
    bought_items = [num_flour_bags, num_egg_crates, num_yeast_bags, num_butter_packs, num_milk_jugs]
    check_if_lost = check_items_enough(bought_items)
    return check_if_lost

#Update and print the list of remaining tasks
def print_task_list(tasks_remaining):
    print("Here are your remaining tasks of the day")
    for i in range(len(tasks_remaining)):
        print(i+1,"-",tasks_remaining[i])

#Validate the player's input to make sure they pick the appropriate task. Ensure
#that the player starts the dough first and bake the baguettes last.
def is_valid_input(index, tasks):
    if len(tasks) == 4:
        if index == 0:
            return True
        elif index == 1 or index == 2:
            print("We should really start the baguette dough first!")
            return False
        elif index == 3:
            print("Whoa, we should probably do everything else first!")
            return False
    elif len(tasks) == 3:
        if index == 0 or index == 1:
            return True
        elif index == 2:
            return False
    elif len(tasks) == 2:
        if index == 0:
            return True
        elif index == 1:
            return False            

#Go through the baking process. Use print_task_list to print the three iterations
#of the tasks list. Use is_valid_input to make sure that the player chooses the
#right tasks in the right order. If the player does the right tasks in the right
#order, then they win the game. If they choose the wrong tasks, then they are
#forced to pick a task again until they get it right
def bake():
    tasks = ["Begin the baguette dough","Make the macarons","Make the croissants","Bake the Baguettes"]
    
    print_task_list(tasks)
    user_choice = int(input("What action would you like to cross off your list next? "))
    check = is_valid_input(user_choice - 1, tasks)
    while check == False:
        print_task_list(tasks)
        user_choice = int(input("What action would you like to cross off your list next? ")) 
        check = is_valid_input(user_choice - 1, tasks)
    print("Ok, let's knead some baguette dough!")
    
    tasks.remove(tasks[user_choice-1])
    print_task_list(tasks)
    user_choice = int(input("What action would you like to cross off your list next? "))
    check = is_valid_input(user_choice - 1, tasks)
    while check == False:
        print_task_list(tasks)
        user_choice = int(input("What action would you like to cross off your list next? "))
        check = is_valid_input(user_choice - 1, tasks)
    if tasks[user_choice - 1] == "Make the macarons":
        print("Adorable sandwich cookies coming right up!")
    elif tasks[user_choice - 1] == "Make the croissants":
        print("Let's make some flaky crescent goodness!")
        
    tasks.remove(tasks[user_choice - 1])
    print_task_list(tasks)
    user_choice = int(input("What action would you like to cross off your list next? "))
    check = is_valid_input(user_choice - 1, tasks)
    while check == False:
        print_task_list(tasks)
        user_choice = int(input("What action would you like to cross off your list next? "))
        check = is_valid_input(user_choice - 1, tasks)
    if tasks[user_choice - 1] == "Make the macarons":
        print("Adorable sandwich cookies coming right up!")
    elif tasks[user_choice - 1] == "Make the croissants":
        print("Let's make some flaky crescent goodness!")

    tasks.remove(tasks[user_choice - 1])
    print_task_list(tasks)
    user_choice = int(input("What action would you like to cross off your list next? "))
    while user_choice != 1:
        print("Bruh, there's only one task remaining! Just do it!")
        print_task_list(tasks)
        user_choice = int(input("What action would you like to cross off your list next? "))

    print("All done! Let's hope we've PRUEven ourselves worthy.")
          
        
    
    
if __name__ == '__main__':
    #Sentinel value to end the game when conditions are met
    have_lost = False
    greeting()
    #the sentinel value is set to go_shopping and if go_shopping returns false,
    #the player loses and doesn't get to bake
    have_lost = go_shopping()
    if have_lost == False:
        bake()
    
        
    
