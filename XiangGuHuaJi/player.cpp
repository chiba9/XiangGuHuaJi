/* XiangGuHuaJi 2016, player.cpp
 *
 * Game <-- Player ---> AI
 *
 */

#include"player.h"

#ifdef _MSC_VER
#include"windows.h"
#endif
#ifdef __GNUC__
#include"dlfcn.h"
#endif

namespace XGHJ {

Player::Player()
{ 
}

Player::Player(string file_name, int id)
    : id(id), file_name(file_name)
{
    player_ai = NULL;

#ifdef _MSC_VER    
    HMODULE hDLL = LoadLibraryA(file_name.c_str());
    if (NULL != hDLL) player_ai = (TPlayerAi)GetProcAddress(hDLL, "player_ai");
#endif
#ifdef __GNUC__
    void* hDLL = dlopen(file_name.c_str(), RTLD_LAZY);
    if (NULL != hDLL) player_ai = (TPlayerAi)dlsym(hDLL, "player_ai");
#endif
    
    Valid = NULL != player_ai;
    
    if (NULL == hDLL) cout << "[ERROR] failed to load \"" << file_name << "\"" << endl;
                 else cout << "Succeed to load \"" << file_name << "\". ";

    if (isValid())
        cout << "Player{" << id << "} has been loaded. " << endl;
    else
        cout << "[ERROR] failed to load Player{"<< id << "} !" << endl;
}

Player::~Player()
{
}

void Player::Run(
    Game&                       game,
    cv::Mat&                    MilitaryCommand_,
    vector<TDiplomaticCommand>& DiplomaticCommandList)
{
    if (!isValid()) return;

    // MilitaryCommand
    vector<vector<TMilitary> >      MilitaryCommand;
    resizeVector(MilitaryCommand, game.PlayerSize, game.PlayerSize);

    // Mask
    cv::Mat OwnershipMask_ = cv::Mat::zeros(game.map.size(), CV_8UC1),
            VisibleMask_ = cv::Mat::zeros(game.map.size(), CV_8UC1),
            ControlMask_ = cv::Mat::zeros(game.map.size(), CV_8UC1);
    vector<vector<unsigned char> >	OwnershipMask, VisibleMask, ControlMask;
    OwnershipMask_ = game.OwnershipMasks_[id].clone();
    for (TId target=0; target<game.PlayerSize; ++target)
    {
        TDiplomaticStatus status = game.Diplomacy[id][target];
        if (status!=Undiscovered && status!=War) 
            VisibleMask_+=game.OwnershipMasks_[target];
        if (status==Union) 
            ControlMask_+=game.OwnershipMasks_[target];
    }
    convertMat(OwnershipMask_, OwnershipMask);
    convertMat(VisibleMask_, VisibleMask);
    convertMat(ControlMask_, ControlMask);

    Info info(
        id,
        game.Round,
        game.map.rows,
        game.map.cols,
        game.PlayerSize,
        OwnershipMask,
        VisibleMask,
        ControlMask,
        game.GlobalMap,
        game.map.MapResource,
        game.map.MapDefenseRatio,
        game.map.MapAttackRatio,
        game.MilitaryMap,
        game.AttackPointsMap,
        game.DefensePointsMap,
        game.PlayerInfoList,
        game.Diplomacy,
        MilitaryCommand,
        DiplomaticCommandList
        );

    try
    {
        player_ai(info);
        convertVector<TMilitary>(MilitaryCommand, MilitaryCommand_);
    }
    catch(exception e)
    {
        cout << "[ERROR] Player " << id << " raised an exception." <<  endl;
        cout << e.what() << endl;
        Valid = false;
    }
    
}

}
