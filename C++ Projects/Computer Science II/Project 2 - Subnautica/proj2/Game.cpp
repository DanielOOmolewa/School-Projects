#include "Game.h"
#include <iostream>
using namespace std;


Game::Game(){
};

void Game::LoadMaterials()
{
    ifstream mat; // Object mat, for file handler
    string name; // String variable, name, for Material.m_name
    string type; // String variable, name, for Material.m_name
    string material1; // String variable, name, for Material.m_material1
    string material2; // String variable, name, for Material.m_material2
    int quantity = 0; // Int variable, quantity, as Material.m_quantity
    int depth; // Int variable, depth, as Material.m_depth

    // Read the content of the file PROJ2_DATA in the array m_materials.
    // Each line in the file is a struct in the array. As each element is added
    // to m_materials, populate the diver's material using AddMaterial with
    // the new element as the parameter.
    mat.open(PROJ2_DATA);
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        string space = " ";
        getline(mat, name, ',');  
        getline(mat, type, ',');
        getline(mat, material1, ',');
        getline(mat, material2, ',');
        mat >> depth;
        getline(mat, space);
        m_materials[i] = Material(name, type, material1, material2, quantity, depth);
        m_myDiver.AddMaterial(m_materials[i]);        
    }
    mat.close();
}

void Game::StartGame()
{
    string diverName; // Instaniate the diver's name
    cout << "50 materials loaded." << endl;
    cout << "What is the name of your Diver?" << endl;
    getline(cin,diverName);
    m_myDiver.SetName(diverName); // Sets the diver's name
    cout << endl;
    LoadMaterials(); 

    int choice = MainMenu(); // The player's choice
    int totalDepth = m_myDiver.CalcDepth(); // The total depth reached

    // Keep asking the player what they would like to do until they enter
    // 5 at the main menu or they have reached a depth of or exceeding MAX_DEPTH
    while ((choice !=5) && totalDepth < MAX_DEPTH)
    {
        // If the user's choice is 1, run m_myDiver.DisplayMaterials()
        // If it's 2, run SearchMaterials()
        // If it's 3, run CombineMaterials()
        // If it's 4, run CalcScore()
        if (choice == 1)
        {
            cout << "\n";
            m_myDiver.DisplayMaterials();
        }
        else if (choice == 2)
        {
            SearchMaterials();
        }   
        else if (choice == 3)
        {
            CombineMaterials();
        }
        else if (choice == 4)
        {
            CalcScore();
        }

        choice = MainMenu();
        totalDepth = m_myDiver.CalcDepth();
    }

    // Congratulate the player if they have reached or exceeded MAX_DEPTH
    // Otherwise, state that they have quit the game and print out "Game Over"
    if (totalDepth >= MAX_DEPTH)
    {
        cout << "Congratulations!" << endl;
        cout << "You have reached a depth of " << totalDepth << endl;
    }
    else if (choice == 5)
    {
        cout << "You have quit the game" << endl;
        cout << "Game Over" << endl;
    }
}

void Game::DisplayMaterials()
{
 // Unused code
 // Prints out the elements of each struct in m_materials
 for (int i = 0; i < PROJ2_SIZE; i++)
 {
    string name_disp = m_materials[i].m_name;
    string type_disp = m_materials[i].m_type;
    string mat1_disp = m_materials[i].m_material1;
    string mat2_disp = m_materials[i].m_material2;
    int quant_disp = m_materials[i].m_quantity;
    int depth_disp = m_materials[i].m_depth;
    int numOnList = i + 1;
    cout << numOnList << ". " << name_disp << ", " << quant_disp << endl;
 }
}

int Game::MainMenu()
{
    // Display the menu and ask what they would like to do
    int player_choice; // The player's choice.
    cout << "What would you like to do?" << endl;
    cout << "1. Display your Diver's Materials" << endl;
    cout << "2. Search for Raw Materials" << endl;
    cout << "3. Attempt to Merge Materials" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    cin >> player_choice;

    // Reprompt the player if they enter an invalid choice
    while (player_choice <= 0 || (player_choice > 5))
    {
    cout << "What would you like to do?" << endl;
    cout << "1. Display your Diver's Materials" << endl;
    cout << "2. Search for Raw Materials" << endl;
    cout << "3. Attempt to Merge Materials" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    cin >> player_choice;
    }

    return player_choice;
}

void Game::SearchMaterials()
{
    // Randomly select a raw material and increased the quantity of said material
    // in the diver's materials by one. Then, print out that said material has been found.
    cout << "\n";
    int rand_ind = rand() % NUM_RAW; // Index of the randomly selected raw material 
    m_myDiver.IncrementQuantity(m_materials[rand_ind]);
    cout << m_materials[rand_ind].m_name << " Found!" << endl << endl;
}

void Game::CombineMaterials()
{
        int choice1 = 0; // The first material the player would like to merge
        int choice2 = 0; // The second material the player would like to merge
        int matIndex1 = 0; // The index of the first material the player chose
        int matIndex2 = 0; // The index of the second material the player chose

        // Keep running RequestMaterial until the player has chosen the materials they
        // would like to merge. Once they have chosen the materials, update matIndex1
        // and matIndex2
        do{
            RequestMaterial(choice1);
        }while(choice1 == -1);
        matIndex1 = choice1 - 1; // Updates the index of the first material the player chose

        do{
            RequestMaterial(choice2);
        }while(choice2 == -1);
        matIndex2 = choice2 - 1; // Updates the index of the second material the player chose

        // Check if there's a least one of each of the materials that the player has chosen
        // to merge are in the known materials
        // If there are at least one of each of the chosen materials in known materials, check to
        // see if they can be merged. Otherwise, tell the user that they do not have enough materials
        // to attempt a marge
        bool checkMatsInInv = m_myDiver.CheckQuantity(m_materials[matIndex1], m_materials[matIndex2]);
        if (checkMatsInInv == 1)
        {
            string matName1 = m_materials[matIndex1].m_name; // Name of the first material the player have chosen to merge
            string matName2 = m_materials[matIndex2].m_name; // Name of the second material the player have chosen to merge

            int comMatInd = SearchRecipes(matName1, matName2); // Potential index of the new material that the two materials make
            // If the potential index does not equal NO_MATCH then get the material struct at the potential index to see 
            // if the name of the material struct equals the name of the first material struct in m_materials
            if (comMatInd != NO_MATCH)
            {
                Material testMat = m_myDiver.GetMaterial(comMatInd); // The material struct at the potential index
                // If the name of the test material does not equal to the name of the first material struct in m_materials,
                // increase the quanity of the merged material by 1 and decrease the quantity of the chosen materials by 1
                if (testMat.m_name != m_materials[0].m_name)
                {
                cout << "\n";
                string comMatName = m_materials[comMatInd].m_name; // Name of the merged material
                m_myDiver.IncrementQuantity(m_materials[comMatInd]);
                cout << matName1 << " combined with " << matName2 << " to make " << comMatName << "!" << endl << endl;
                m_myDiver.DecrementQuantity(m_materials[matIndex1]);
                m_myDiver.DecrementQuantity(m_materials[matIndex2]);
                }
            }
            // If the potential index does equal NO_MATCH, then tell the user that no recipe exists for the chosen materials
            else if(comMatInd == NO_MATCH)
            {
                cout << "\n";
                cout << "No recipe exists for " << matName1 << " and " << matName2 << endl << endl;
            }
        }

        else if (checkMatsInInv == 0)
        {
            cout << "\n";
            cout << "You do not have enough " << m_materials[matIndex1].m_name << " or ";
            cout << m_materials[matIndex2].m_name << " to attempt that merge" << endl << endl;
        }

}

void Game::RequestMaterial(int &choice)
{
    // Prompt the user what materials they would like to merge
    // Reprompt them if they enter an invalid choice
    do{
        cout << "\n";
        cout << "Which materials would you like to merge?" << endl;
        cout << "To list known materials enter -1" << endl;
        cin >> choice;
        cout << endl;
    }while (choice < -1 || choice > 50 || choice == 0);

    // If the user's choice is -1, display the known materials
    if (choice == -1)
    {
        cout << "\n";
        m_myDiver.DisplayMaterials();
    } 
}

int Game::SearchRecipes(string item1, string item2)
{
    // Go through the list of materials until an element's material1 and material
    // matches with item1 and item2 (or vice versa). Once the said element is found,
    // return it's index. Otherwise, if no such element is found, return NO_MATCH
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        string mat1 = m_materials[i].m_material1;
        string mat2 = m_materials[i].m_material2;
        if ((item1 == mat1 && item2 == mat2) || (item1 == mat2 && item2 == mat1))
        {
            return i;
        }
    }
    return NO_MATCH;
    
}

void Game::CalcScore()
{
    // Calculate the score by running m_myDiver.CalcDepth()
    // Once the score is calculated, print out the maximum depth
    // and the diver's depth
    cout << "\n";
    int score = m_myDiver.CalcDepth();
    cout << "***The Diver***" << endl;
    cout << "The Great Diver " << m_myDiver.GetName() << endl;
    cout << "Maximum Depth: " << MAX_DEPTH << endl;
    cout << "Current Depth: " << score << endl << endl;

}


