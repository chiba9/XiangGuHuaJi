#2016年自动化系 香菇滑稽大赛

- 编译条件：

  - Visual Studio 2012(VC11)（如果不想这么干，请ignore掉项目文件）
  - Opencv 2.4.10（必须）
  - 请自行编辑属性表文件并且放置到项目目录下（与.vcproj同目录），两个配置文件的名称分别为OpenCV_release_property.props和OpenCV_debug_property.props，这是写死在.vcproj里的（如果不想这么干，请ignore掉项目文件）
  -  **各项目的简介请参见各项目的readme.md文件**

- 以下是规则书


#香菇滑稽 Version2 Update2

> 修订：wxk14\Du<br>
> 规则：Du <br>
> 鸣谢：Pierre ;Starlight 

## 剧本

参见https://github.com/hzsydy/XiangGuHuaJi/tree/master/Scenarios

## 游戏模式

【赛程慢慢来嘛】

- 积分赛~~天梯模式~~

  根据标准规则和标准地图进行 *一局比赛* 。标准地图是公开的。

  关于 *一局比赛* 的定义，参见本段最后。

- 初赛

  初赛的时候将根据标准规则和初赛特制的地图进行 *一轮比赛* ，前7名进入决赛（刨掉乱斗模式的胜利者之外的）

  关于 *一轮比赛* 的定义，参见本段最后。

- 乱斗模式

  每两周一次，采用特别制定的地图和特别制定的胜利条件和特殊规则，决出胜负。每个乱斗周期结束的时候，进行 *一轮比赛* ，前三名作为本届乱斗的优胜者保送进入决赛。【并且应该还有其他优惠】

  特制地图将在该轮次乱斗的前一周公布。

- 决赛

  决赛将采用标准规则和决赛特制的地图进行 *一轮比赛*。

- 一局比赛的定义

  一局比赛中，将由赛程规定数目的玩家参与比赛，获得初始资源，并且决出优胜者（或相对优胜者）。关于如何决出优胜者，参见 **游戏规则-胜利条件** 。

- 一轮比赛的定义

  一轮比赛将由若干局比赛组成。在第一局比赛中，所有玩家的出生点将获得等量的资源。从第二局比赛开始，上一局中的优胜者（或相对优胜者）获得上一局初始资源的1.5倍。持续此过程，直到有玩家的初始资源为原来资源的1.5^5倍，则此玩家获得优胜并从下一局游戏开始被剔除。持续此过程直到足够多的玩家（赛程规定数目的玩家）获得优胜。

## 游戏规则

###概述

战争模拟游戏

- 玩家消耗资源建立城市
- 城市对土地施加影响力以夺取土地主权
- 国家领土为之提供资源

###胜利条件
- 歼灭其他所有国家
- 限定回合后土地最/较多的国家
- 在乱斗模式中，第一个完成满足剧本特殊要求的国家

###土地与资源

- 地图尺寸是给定的，预计最大50*50
- 土地的主权
  - 土地主权有两种状态：中立，某国领土
  - 游戏开始时，除了出生点，所有土地都是中立的
  - 土地主权判定参见**城市与影响力**

- 土地的资源
  - 每块土地有不同的资源
  - 国家出生点上保证有资源（初始资源）
  - 每回合国家都会得到总领土资源和的资源量；而中立的土地资源直接流失
  - 国家可以保存自己资源以供不时之需
  - 【存的太多会有很严重的通货膨胀debuff 且 城市对附近的领土资源有加成，总之要打压一波流】
- 土地的地形
  - 每块土地有不同的地形
  - 地形有两个参数：攻击系数和防御系数，参见**城市与影响力**
- 土地的特殊效果
  - 乱斗规则特有，由剧本指明

###城市/兵力与影响力

说明： 城市/兵力 在游戏中是一个意思。所有的城市/兵力一旦被放置，就不能

- 城市的建立与发展
  - 游戏开始时，一个国家有一个出生点，且出生点上有一个等级1的城市。
  - 国家可耗费 k * c 的资源量，在本回合己方领土上建立一个k级的城市，或将自己某个城市的等级增加k级。也即，空地相当于0级城市。
  - 你也可以在同盟国的领土内建立你自己的城市。
    - 战术价值：在他国领土边境处英勇击敌夺得**自己**的领土，同时自己没有额外丢失领土的危险。
    - 风险：一旦同盟被取消，你将被迫以很低的价格撤回这些没有建在本国领土上的城市；而且此时因为军通的问题，你新打出来的领土可能没有任何防御能力。
    - 一块地上可以同时分布不同AI的兵力。
      - 一块土地上甚至可以同时分布两个正在战争中的国家的兵力(AB同盟，AC同盟，BC战争；A的领土上同时出现BC)。稍后会说明，所有的攻击都是针对**领土**而不是针对兵力的。
- 影响力
  - 城市将对周围的大面积土地产生影响力。影响力随城市等级递增，随城市距土地的距离递减。
    - **TODO**:【影响力函数的设计】
  - 军通
    - 影响力受到图的连通性影响。如果有 非同盟国家 阻隔，你的城市影响力将传播一格之后结束。
      - 所以，在没有新的兵力部署的条件下，不论兵力多么悬殊，你一回合最多攻下对方一格的领土。更高效的攻击方式见“连破判定"。
    - 如果我方领土被切断成了两部分，又没有盟友能够提供连通的道路，则两个区域的影响力分别计算。
      - 被一格宽度切断时，两侧都可以对切割点施加攻击影响力。但因为没有办法穿过切割点施加影响力，所以两侧防御影响力只能分别计算。
- 土地主权判定
  - 以下称每个能对这块土地施加攻击力影响，不拥有此块土地主权的AI为一个攻击方AI；称控制这块土地的AI为防御方AI。
    - **每个攻击方** 都有一个 **攻击进程**，记录对这块土地相互独立的攻击进程。 //**TODO**
    - 一块土地 **只有一个防御力** 。此防御力通过同盟联防计算得到。
  - 更新攻击进程
    - 每个攻击方的攻击进程 增加 攻击AI对此块土地的影响力 * 地形的攻击系数 
    - 每个攻击方的攻击进程 减少 防御同盟AI对此土地的影响力之和 * 地形的防御系数
  - 逐个检查每个攻击方的攻击点数，如果有任意一个攻击方的 攻击进程 超过阈值，则进入击破判定
    - 击破判定
      - 如果有多个攻击方在此回合都超过了攻击进程阈值，则攻击进程最高的攻击方获得此块土地。
      - 领土被击破的回合：清空土地上的兵力（不会回收资源），清空所有攻击进程；新的主权国将在此回合收取此领土的资源；
    - 连破判定
      - 连破判定专为加快游戏进程设计：在 **成功击破** 的回合，对 **新放置的兵力** 重新计算一次影响力
      - 计算**连破影响力**时，被攻破一方的领土 和 无主领土 都会加入你的军通，新放置的城市将一次性的对大面积的领土施加攻击影响力。
        - 在游戏初期开荒时：看好时机，一回合释放一批兵力触发连破判定，可能比每个回合都放置很少的城市开荒效果好。
        - 在两军对峙时：在两军交界处，在合适的回合一次性放出大量兵力，可以快速切断防线并一次性攻得大片未设防领土
- 战术价值：将太弱的城市群清场，快速扩张，切断军通构成包围，紧急回连突破包围封锁
- 风险：想要达到战略价值就必须快速投入大量资源；效果只会持续一回合，且后备军不足就很可能被反包围；如果己方边境附近已经塞满了城市，这个buff无计可施；

    
  -  如果一个AI在一回合内瞬间控制了一块地（即从差X变为高X），则获得overrun（所谓“连破”）效果，即这块地视作对这个AI有军通，并且计算由于这块地有军通导致能够新的能够攻击到的土地上产生的影响力
     -  这个过程是可以一直持续下去直到无法继续扩张的，所以如果你在一个点处一次投入了大量城市，可能会一路overrun下去，导致下回合获得很大的一块新领土。~~大炸弹什么的，康神表示大喜び~~
     -  由于地形的存在，关键隘口被瞬间击破之后后面可能会因为无险可守而瞬间垮掉一大片。
     -  有些地形是不可通过的（防御系数无穷大），~~这时候你可能观察到明显的衍射现象,滑稽~~。
     -  ~~如果同时有两个攻击方丢大炸弹的话，你会观察到明显的干涉现象，滑稽~~。
  -  一个AI对于一块土地的影响力最多只能比其他AI高X。即，如果一块地的攻击方影响小于防御方影响，那么这块地在下回合将维持当前影响力状态不变（反之，这块地将至少变为中立，或者变为攻击方所属）
     - 如果领土的归属权从一个AI转移到另一个AI，则领土上的原AI城市被破坏。
  -  每个攻击方AI对这块土地的影响力只由自己造成；防御方AI对这块土地的影响力由自己以及自己战争中的盟友造成。关于"战争中的盟友"，参见**国家与外交**部分
    
###国家与外交

- 视野
  - 外交关系决定了你的视野（地图视野 + 国家内政视野）。
  - 地图视野
    - 你知道每一块土地上的资源和攻防参数，但地图视野的限制使得你不能始终知道每一块土地的
      - 主权国ID，此块土地上各个玩家的兵力数量，此点当前防御力总分，此点当前每位玩家攻击力总分
    - 你的视野为：对你联盟的国家领土以及附近的1格范围 + 对你中立/停战的国家领土。
  - 国家内政视野
    - 战争/未发现：你无法获得此国家的任何内政信息
    - 中立/停战：你可以获得此国家的
      - 领土总面积，当前兵力总量
    - 同盟：你可以获得此国家的
      - 领土总面积，当前兵力总量，当前库存总量
- 侵犯  
  - TODO
  - “侵犯”只会发生在战争的国家之间。
  - 从宣战的回合开始，两国的兵力将开始在对方的领土上施加攻击力。
  - 在战争被取消（双方的态度都变成KeepNeutral/AskForUnion）的回合，双方施加在对方领土上的攻击力清零。
- 联防
  - 同盟国家可以在对方的领土内放置兵力。
  - 计算己方领土防御力时，所有你的同盟国家兵力都计算在内。
  - 在退出同盟（任何一方的态度变成KeepNeutral/DeclareWar）的回合
    - 联防立即失效：立即重新计算你的领土的防御力。战争期间可能导致你的领土被瞬间击破。
    - 双方被迫回收放置在对方领土上的兵力：这些兵力将在此回合**立即**消失，同时你的资源量增加你回收的兵力价值的一半。
- 国际关系
  - Undiscovered 未发现：还没有发现的国家
    - 无视野；不侵犯；不联防；
  - Neutral 中立：观察到国家之后的默认状态
    - 有视野；不侵犯；不联防；
  - StopWar 停战：等于中立，但x回合内不能宣战
    - 有视野；不侵犯；不联防； 
  - Union 同盟
    - 有视野；不侵犯；联防；
    - 自己对自己的国际关系始终标记为同盟。
  - War 战争
    - 无视野；侵犯；不联防；
- 外交态度
  - 包括三种：保持中立、默许同盟、战争
  - 各状态下可以采取的外交态度
    - 未发现
      - 外交态度强制为保持中立
    - 中立 / 停战
      - 默许同盟
        - 由对方外交态度决定，回合结束后的状态将是（括号内为对方对你的态度）
          - 同盟（默许同盟）
          - 中立（保持中立）
          - 战争（战争）
      - 保持中立(default)
        - 由对方外交态度决定，回合结束后的状态将是
          - 中立（保持中立，默许同盟）
          - 战争（战争）
      - 宣战（停战状态下，此态度将作为“继续中立”处理）
        - 回合结束时的状态将是
          - 战争
        - 【可以在战争的回合打出第一波攻击】
        - 从中立转为战争的这一回合（即宣战），被宣战的AI的所有同盟AI，如果与宣战AI处于中立状态，则同时自动与宣战AI进入战争状态。
    - 同盟
      - 继续同盟(即“默许同盟”，default)
        - 由对方外交态度决定，回合结束后的状态将是
          - 同盟（继续同盟）
          - 停战（解除同盟）
      - 解除同盟（即“保持中立”或“战争”）
        - 回合结束时的状态将是
          - 停战
    - 宣战
      - 继续战争(即“战争”，default)
        - 回合结束时的状态将是
          - 战争
      - 请求停战（包括“默许同盟”和“保持中立”）
        - 由对方外交态度决定，回合结束后的状态将是
          - 战争（继续战争）
          - 停战（请求停战）

- 战争中的盟友
  - 如果两个AI处于同盟，并且对同一个AI宣战，那么这两个AI被视作“战争中的盟友”。在战争中，防御时影响力叠加计算。

###回合时序

- （第一回合特有）选择出生点
- 建造
  - 在自己或同盟国家，建立或升级城市
- 外交
  - 更新国家的外交状态
- 战争
  - 计算全图的影响力变更
  - 如果发生了overrun现象，则递归计算全图的影响力变更直到不再发生overrun。
- 检查胜负
