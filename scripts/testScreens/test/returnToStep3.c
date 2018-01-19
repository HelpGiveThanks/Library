January 15, 2018 15:09:48 Library.fmp12 - returnToSubsections -1-
test: test: returnToSubsections
#
#Close any open test item reference windows
#and resize the two remaining windows.
Close Window [ Name: "Reference"; Current file ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2 ]
Select Window [ Name: "Tag Menus"; Current file ]
#
#Return to this test's subsection menu, setting
#the Tag Menus window to show no tags,
#because there are no tags to show.
Go to Layout [ “testMenuNoTag” (TEMP) ]
Select Window [ Name: "Test"; Current file ]
Set Field [ TEMP::showFavorites; "" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Variable [ $$stopLoadingTestSubSection ]
