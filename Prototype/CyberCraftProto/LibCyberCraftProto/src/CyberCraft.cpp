//
// Created by jngl on 18/08/2020.
//

#include "CyberCraft.h"

#include "System.h"

const char* gameMap =
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
        "~~~~~~     ~~~~~~~~~~~     ~~~~~"
        "~~           g~~~~           g~~"
        "~       g               g      ~"
        "~   T      R   g    T      R   ~"
        "~    g              g          ~"
        "~           g          P    g  ~"
        "~  g      T        g      T    ~"
        "~            g                 ~"
        "~    R      g        R      g  ~"
        "~ g               g            ~"
        "~       g       R       g      ~"
        "~     T     g        T     g   ~"
        "~~         g       g       g   ~"
        "~~            T                ~"
        "~~~    g       g      g   g    ~"
        "~~~       T                    ~"
        "~~           g     g     T    ~~"
        "~       g               g     ~~"
        "~   T      R        T      R  ~~"
        "~    g         R     g        ~~"
        "~          g                g ~~"
        "~  g      T        g      T   ~~"
        "~                             ~~"
        "~    R      g    T   R      g ~~"
        "~ g               g           ~~"
        "~       g               g     ~~"
        "~     T     g         T     g ~~"
        "~~         g             g   ~~~"
        "~~~~~~~~~~              ~~~~~~~~"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

CyberCraft::CyberCraft(cc::Ref<ck::RenderContext2D> renderContext, cc::Ref<ck::Window> win):
        m_renderContext(renderContext),
        m_window(win)
{
    texture = renderContext->getHandleFromFile("./data/tileset.png");
    renderContext->loadTexture(texture);

    m_world.forEach([this](int x, int y, Bloc& bloc){
        char tile = gameMap[y*World::sizeX+x]; // NOLINT
        if(tile == 'T'){
            bloc = Bloc::Tree;
        }else if(tile == '~'){
            bloc = Bloc::Water;
        }else if(tile == 'R') {
            bloc = Bloc::Stone;
        }else if(tile == 'g'){
            bloc = Bloc::LongGrass;
        }else if(tile == ' ') {
            bloc = Bloc::Grass;
        }else if(tile == 'P'){
            player.pos.x = static_cast<float>(x);
            player.pos.y = static_cast<float>(y);
            bloc = Bloc::Grass;
        }
    });

//    for(int x=0; x<World::sizeX; ++x){
//        for(int y=0; y<World::sizeY; ++y){
//            if(m_world.isInGroup(x, y, getBlocGroup("Water"))){
//                constexpr const BlocGroup& grassGroup = getBlocGroup("Grass");
//
//                constexpr unsigned int left  = 0b0001;
//                constexpr unsigned int right = 0b0010;
//                constexpr unsigned int north = 0b0100;
//                constexpr unsigned int south = 0b1000;
//
//                unsigned int neighbourGrass = 0;
//                if(m_world.isInGroup(x-1, y, grassGroup)){
//                    neighbourGrass |= left;
//                }
//                if(m_world.isInGroup(x+1, y, grassGroup)){
//                    neighbourGrass |= right;
//                }
//                if(m_world.isInGroup(x, y-1, grassGroup)){
//                    neighbourGrass |= north;
//                }
//                if(m_world.isInGroup(x, y+1, grassGroup)){
//                    neighbourGrass |= south;
//                }
//
//                if(neighbourGrass == south){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassSouth");
//                }else if(neighbourGrass == north){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassNorth");
//                }else if(neighbourGrass == left){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassLeft");
//                }else if(neighbourGrass == right){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassRight");
//                }else if(neighbourGrass == (right | north)){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassNorthRight");
//                }else if(neighbourGrass == (left | north)){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassNorthLeft");
//                }else if(neighbourGrass == (right | south)){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassSouthRight");
//                }else if(neighbourGrass == (left | south)){
//                    m_world.getBloc(x, y) = &getBlocInfo("WaterGrassSouthLeft");
//                }
//            }
//        }
//    }
}

void CyberCraft::update() {
    movePlayer(m_window, cc::make_ref(player.pos), m_world);
}

void CyberCraft::draw() {

    m_world.forEach([this](int x, int y, Bloc bloc){
        cc::Vector2f pos{static_cast<float>(x), static_cast<float>(y)};
        drawSprite(m_renderContext, texture, pos, getBlocInfo(bloc).sprite);
    });

    drawSprite(m_renderContext, texture, player.pos, player.sprite);
    m_renderContext->setViewCenter(player.pos);
}

CyberCraft::~CyberCraft() {
    m_renderContext->unloadTexture(texture);
}

