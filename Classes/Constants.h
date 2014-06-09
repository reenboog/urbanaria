#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define kAITest 0
#define kPlayerTest 0

#define kPurchaseTimeout 10

// Gem visual 

#define kZOrderGem 2
#define kZOrderTile 3

#define zBattleGUI 10

// GemField time 

#define kSpeedFactor 1

#define kSwapTime 0.15f / kSpeedFactor
#define kFallTime 0.1f / kSpeedFactor
#define kDestructionTime 0.15f / kSpeedFactor
#define kTransformationTime 0.25f / kSpeedFactor

// GemField 

#define kFieldWidth 9
#define kFieldHeight 6
#define kGemConcentration 0.0185f

#define kGemTypeAmount 7
#define kBonusChance 0.0f

// GameScene 
#define kNumberOfPlayers 2

#define kTipDelay 4.f
#define kAITurnDelay 0.5f / kSpeedFactor

#define kSpawnBonuses 0

// Config 
const bool kFetchConfig = true;
const bool kPreloadField = false;
const bool kLoadPlayersFromConfig = false;

// Equipment and magic 
#define kEquipmentSlotsAmount 5
#define kDefaultSpellSlotsAmount 3
#define kMaxSpellSlotsAmount 4

#define kEquipmentBonusStatPercentage 0.5

// Game length
#define kNumberOfAttacks 8
#define kMinHits 4
#define kNormalizeAttacks true
#define kManaFillRate 6

// World 
#define kLevelsPerWorld 13

#define kAvatarMaxIndex 49

#define kMaxRewardsPerWorld 3

#define kBranchChance 1.25

#define kBranchOneStart 4
#define kBranchTwoStart 6
#define kBranchThreeStart 9

#define kGrailChance 1.25

// SceneTransition 
#define kSceneSwitchTime 0.25f
#define kZOrderBlackout 50
#define kZOrderActive 12
#define kZOrderDisabled 5 
#define kBlackoutTransparency 170

#define kExpPerEnemyLevel 60
#define kGoldPerEnemyLevel 30

#define kDefaultGoldAmount 150
#define kDefaultJewelsAmount 10

#define kJewelsForRepair 3
#define kJewelsForSlot 25
#define kJewelsForRevive 2
#define kJewelsReward 3

#define kEquipmentExpPerBattle 1

#define kFilterItems true

// Money menu

#define kBuyLittleGoldTag 11
#define kBuyAverageGoldTag 12
#define kBuyMuchGoldTag 13

#define kBuyLittleJewelsTag 21
#define kBuyAverageJewelsTag 22
#define kBuyMuchJewelsTag 23
#define kBuyExtraJewelsTag 24

#define kBuyLittleGoldAmount 500
#define kBuyAverageGoldAmount 2000
#define kBuyMuchGoldAmount 5000

#define kBuyLittleJewelsAmount 10
#define kBuyAverageJewelsAmount 25
#define kBuyMuchJewelsAmount 70

#define kBuySpecialJewelsAmount 9
#define kBuySpecialJewelsTag 24

#define kStripeMenuButtonOffset 0.45f

#define kMapSceneTag 700
#define kBuyMoneyScreenTag 42
#define kContinueGameScreenTag 911
#define kPreGameScreeenTag 808
#define kChestMenuScreenTag 999
#define kGrailsMenuTag 777
#define kItemOfferMenuTag 742
#define kPauseMenuTag 444
#define kPurchaseBlockerTag 505

#define kAITurnActionTag 129

#define kRevivalHealthPercentage 0.5

#define kGoldChestCost 100
#define kJewelsChestCost 5
#define kTimeChestCost 600

#define kHealthEffectIcon 5
#define kManaEffectIcon 15
#define kArmourEffectIcon 8
#define kDamageEffectIcon 10

#define kGemHealthPath "gemHealth.png"
#define kGemManaPath "gemMana.png"
#define kGemHealthManaPath "gemHealthMana.png"
#define kGemMoneyPath "gemMoney.png"
#define kGemExpPath "gemExp.png"
#define kGemAttackPath "gemAttack.png"
#define kGemShieldPath "gemShield.png"

enum GemColour {
	GC_Random,
	GC_Health,
	GC_Mana,
	GC_HealthMana,
	GC_Shield,
	GC_Attack,
	GC_Money,
	GC_Exp,
	GC_Wild,
};

enum GemState {
	GS_Idle,
	GS_Moving,
	GS_Moved,
	GS_Selected,
	GS_Matched,
	GS_Transforming,
	GS_Transformed,
	GS_Destroying,
	GS_Destroyed,
	GS_Immovable
};

enum GemType {
	GT_Colour,
	GT_Cross,
	GT_LineHor,
	GT_LineVer,
	GT_Explosion
};

enum Direction {
	D_Down,
	D_Up,
	D_Left,
	D_Right,
};

enum FieldState {
	FS_Ready,
	FS_Waiting,
	FS_Moving,
	FS_Searching,
	FS_Transforming,
	FS_Destroying,
	FS_Refilling,
	FS_Shuffling,
	FS_Generating,
	FS_Flushing,
};

enum PlayerAttribute {
	PA_Health,
	PA_Mana,
	PA_Shield,
	PA_Attack,

	PA_CriticalChance,
	PA_CriticalDamage,
	PA_DodgeChance,
	PA_BlockChance,
	PA_ResistChance,
};

enum AttributeType {
	AT_Max,
	AT_Current,
	AT_Percentage,
	AT_Regen,
	AT_Leech,
	AT_OnMove,
	AT_OnAttack,
	AT_OnCast,
	AT_Chance,
};

enum EquipmentSlot {
	ES_Head,
	ES_Body,
	ES_Legs,
	ES_Weapon,
	ES_Trinket,
	ES_Unknown,
};

enum Currency {
	C_Gold,
	C_Jewels,
};

enum Reward {
	R_Gold,
	R_Jewels,
	R_Equipment,
	R_Item,
};

enum AvatarType {
    AV_Player,
    AV_Enemy
};

enum Chest {
	CH_Time,
	CH_Gold,
	CH_Jewels,
};

#if(kSpawnBonuses == 1) 
	const GemType kVerticalMatchFourBonus = GT_LineVer;
	const GemType kHorizontalMatchFourBonus = GT_LineHor;
	const GemType kVerticalMatchFiveBonus = GT_LineVer;
	const GemType kHorizontalMatchFiveBonus = GT_LineHor;
	const GemType kCrossMatchBonus = GT_Cross;
#else
	const GemType kVerticalMatchFourBonus = GT_Colour;
	const GemType kHorizontalMatchFourBonus = GT_Colour;
	const GemType kVerticalMatchFiveBonus = GT_Colour;
	const GemType kHorizontalMatchFiveBonus = GT_Colour;
	const GemType kCrossMatchBonus = GT_Colour;
#endif

#define kSpeed 0.8f

#define kFieldShowTime (0.15f * kSpeed)
#define kPauseShowTime (0.5f * kSpeed)
#define kSpellsShowTime (0.2f * kSpeed)
#define kAvatarShowTime (0.2f * kSpeed)
#define kInventoryShowTime (0.2f * kSpeed)
#define kBorderShowTime (0.1f * kSpeed)
#define kOrnamentShowTime (0.15f * kSpeed)
#define kDragonShowTime (0.1f * kSpeed)
#define kMarginTime (0.1f * kSpeed)

#define kChartboostFreq 6


// Fonts

#define kButtonCaptionFont "myriadBold20.fnt"

#define kStatsHeaderFont "myriadBold20Black.fnt"
#define kStatsNumbersFont "myriadRegular20Black.fnt"
#define kStatsNamesFont "myriadRegular20Black.fnt"

#define kPlayerHeadersFont "myriadBold20Black.fnt"
#define kPlayerStatsFont "myriadRegular20Black.fnt"
#define kPlayerItemsFont "myriadBold20.fnt"

#define kShopNameFont "myriadBold20Black.fnt"
#define kShopDescriptionFont "myriadRegular20Black.fnt"
#define kShopButtonFont "myriadBold20.fnt"
#define kShopStatsFont "myriadRegular20Black.fnt"
#define kShopMoneyFont "myriadRegular20Black.fnt"
#define kShopMoneyButtonFont "myriadRegular20Black.fnt"
#define kShopMoneyAmountFont "myriadBold20Black.fnt"
#define kShopDiscountFont "myriadBold20White.fnt"

#define kGrailsNameFont "myriadBold20Black.fnt"
#define kGrailsDescriptionFont "myriadRegular20Black.fnt"

#define kPreGameStatsFont "myriadRegular20Black.fnt"
#define kPreGameFightFont "myriadSemibold41White.fnt"
#define kPreGameDescriptionFont "myriadRegular20Black.fnt"

#define kPostGameExpFont "myriadRegular20Black.fnt"
#define kPostGameMoneyTotalFont "myriadRegular20Black.fnt"
#define kPostGameMoneyEarnedFont "myriadBold20.fnt"
#define kPostGameRewardFont "myriadRegular20Black.fnt"
#define kPostGameButtonFont "myriadBold20.fnt"
#define kPostGameBubbleFont "myriadRegular20Black.fnt"

#define kCombatStatsFont "ingameStats.fnt"
#define kCombatIndicatorFont "myriadBold20Black.fnt"
#define kCombatEffectFont "ingameStats.fnt"
#define kCombatManaFont "myriadBold20.fnt"
#define kCombatItemsFont "myriadBold20.fnt"
#define kCombatDialogueFont "myriadRegular20Black.fnt"
#define kCombatNoTurnsFont "myriadSemibold41White.fnt"

#define kStripeTextFont "myriadBold20Black.fnt"
#define kStripeButtonFont "myriadBold20.fnt"

#define kChestRewardFont "myriadBold20.fnt"
#define kChestCaptionFont "myriadBold20.fnt"

// sounds

#define kBattleBackgroundMusic "battleMusic.mp3"
#define kMapBackgroundMusic "mapMusic.mp3"

#define kButtonTapSound "btnTap0.mp3"
#define kChestOpenSound "chestOpen.mp3"
#define kClothSound "cloth.mp3"
#define kCoinSound "coin.mp3"
#define kCritSound "crit.mp3"
#define kDodgeSound "dodge.mp3"
#define kElixirUseSound "elixirUse.mp3"
#define kExpSound "exp.mp3"
#define kExplosionSound "explosion.mp3"
#define kExtraMoveSound "extraMove.mp3"
#define kFlagAppearSound "flagAppear.mp3"
#define kLevelUpSound "levelUp.mp3"
#define kExpFillSound "expFill.mp3"
#define kGemMatchSound "gemMatch.mp3"
#define kGemTapSound "gemTap1.mp3"
#define kHealSound "heal.mp3"
#define kHeartBeatSound "heartBeat.mp3"
#define kItemAppearSound "itemAppear.mp3"
#define kItemRepairRequiredSound "itemRepairRequired.mp3"
#define kManaSound "mana.mp3"
#define kNewBloodlineSound "newBlodline.mp3"
#define kNoMovesSound "noMoves.mp3"
#define kPurchaseCoinsSound "purchaseCoins.mp3"
#define kScoreCountSound "scoreCount.mp3"
#define kSpellUseSound "spellUse.mp3"
#define kSwordSound "sword%i.mp3"
#define kSwordNumOfSound 5
#define kWrongMoveSound "wrongMove.mp3"
#define kYouLoseSound "youLose.mp3"
#define kYouWinSound "youWin.mp3"

// end of sounds

// will be moved to Constants.h later
////////////////////////////////////////////////////////////////////////
#define kCharacterAvatarGUIPrefix "character"

#define kPlayerGUIAvatarFrameSpriteName "playerAvatarFrame.png"

#define kDodgeKey "eventDodge"
#define kCriticalKey "eventCritical"
#define kExtraKey "eventExtra"

#define zGUIAvatar -1
#define zGUIHPProgress 15
#define zGUIManaProgress 15
#define zGUIArmourProgress 15
#define zGUIAvatarFrame 12
#define zGUISpells 15
#define zGUIAvatarEffect 11
#define zNumbers 19

#define kPlayerGUIAvatarTag 1000
#define kEnemyGUIAvatarTag 1001

#define kGUIProgressBarSpriteName "barImage.png"
#define kGUIHPProgressBarSpriteName "healthBar.png"
#define kGUIManaProgressBarSpriteName "manaBar.png"
#define kGUIArmourProgressBarSpriteName "shieldBar.png"

#define kSpellTintImagePath "spellSlotTint.png"
#define kSpellFrameImagePath "spellSlotFrame.png"
#define kSpellFrameImageDisabledPath "spellSlotFrameDisabled.png"
#define kSpellFrameImageActivePath "spellSlotFrameActive.png"
#define kSpellIconPath "spellIcon"
#define kSpellSlotIconPath "spellEmpty.png"
#define kEffectIconPath "effectIcon"
#define kConsumableFramePath "consumableFrame.png"
#define kOrnamentPath "ornament.png"
#define kConsumableDummyPath "consumableEmpty.png"

#define kLabelShadePath "labelShade.png"

#define zSpellTintImage 0
#define zSpellMenuItme 2
#define zSpellIcon -2
#define zSpellCost 4
#define zManaCostLabel 6

#define kSpellTintOpacity 120

#define kItemContainerPath "inventoryPanel.png"
#define kItemButton "consumableButton.png"
#define kItemButtonActive "consumableButtonActive.png"
#define kItemButtonDisabled "consumableButtonDisabled.png"
#define kItemTintImage "consumableTint.png"
#define kItemIconPath "consumableIcon"
#define kItemArrowPath "consumableArrow.png"

#define kEventIndicatorPath "eventIndicator.png"

#define kBorderTopPath "borderTop.png"
#define kBorderTopCornerPath "borderTopCorner.png"
#define kBorderBotCornerPath "borderBottomCorner.png"
#define kBorderSidePath "borderSide.png"
#define kBorderBotPath "borderBottom.png"

#define kPausePanelPath "pausePanel.png"
#define kPauseButtonPath "pauseButton.png"
#define kPauseButtonPressedPath "pauseButtonPressed.png"

#define kRunTime 0.75f

#define kIndicatorShowTime 0.5f
#define kIndicatorStayTime 2
#define kIndicatorHideTime 0.25f

#define kNumberOfConsumablesDisplayed 12

#define zBorders 20
#define zTip 25

#define kConfirmButtonPath "confirmButton.png"
#define kDismissButtonPath "dismissButton.png"
#define kConfirmButtonPressedPath "confirmButtonPressed.png"
#define kDismissButtonPressedPath "dismissButtonPressed.png"

#define kNextKey "nextCue"
#define kSkipKey "skipDialogue"
#define kConsumableTipKey "tipConsumables"

#define kLabelExtraKey "labelExtraTurn"

#define kDangerPercentage 25
#define kDangerFadeTime 1
#define kDangerImagePath "danger.png"

#define kNumberOfEffectRows 2

////////////////////////////////////////////////////////////////////////

#define SafeDelete(p) {if(p) {delete p; p = NULL;}}
#define SafeRemoveChild(p){if(p){removeChild(p); p = nullptr;}}

#endif // __CONSTANTS_H__