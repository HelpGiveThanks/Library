testScreens: test: returnToStep3
// Set Field [ InspectItems::glocationNameGlobal; $$contactName & ": " & $$locationName ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Layout [ “testMenuNoTag” (TEMP) ]
Select Window [ Name: "Test"; Current ﬁle ]
Set Field [ TEMP::showFavorites; "" ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
January 7, 平成26 12:33:51 Imagination Quality Management.fp7 - returnToStep3 -1-
