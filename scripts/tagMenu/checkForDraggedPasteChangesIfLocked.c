January 20, 2018 18:10:01 Library.fmp12 - CHUNKcheckForDragPasteChanges -1-
tagMenu: CHUNKcheckForDragPasteChanges
#
#
#Used by script changeSpellingOfKeywordOrNodeTag
#removeTextFormattingAndCommas
If [ Get (LayoutTableName) = "tagMenus" ]
#
#Exit any fields so do not get can't modify error message
#because record is in use in another window.
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has change it back
#to the way it was, unless the change was made in the
#field the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
#
#Group name check EXCEPT for
#test item group names.
If [ Get (LayoutName) ≠ "setupTestItem" ]
If [ tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ≠ "testItemGroup" ]
If [ tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ≠ tagMenuGroup::name and
$$Tag ≠ tagMenuGroup::_Lgroup and
$$citationMatch ≠ "testItem" ]
Set Field [ tagMenuGroup::name; tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
End If
End If
End If
#
#Test item group name check.
If [ Get (LayoutName) = "setupTestItem"
 or
tagMenuGroup::nameSpellingEXCEPTForTestItemGroup = "testItemGroup" ]
If [ tagMenuTestItemGroup::name ≠ tagMenuTestItemGroup::nameSpellingFORTestItemGroup and
$$Tag ≠ tagMenuTestItemGroup::_Lgroup and
//Test item group match field is the name spelling check field for other tag groups.
tagMenuTestItemGroup::nameSpellingEXCEPTForTestItemGroup = "testItemGroup" ]
Set Field [ tagMenuTestItemGroup::name; tagMenuTestItemGroup::nameSpellingFORTestItemGroup ]
End If
End If
#
#Tag name check.
If [ tagMenus::tag ≠ tagMenus::tagSpelling ]
If [ $$tag ≠ "" and $$tag ≠ tagMenus::_Ltag
 or
$$tag = ""
 or
tagCreatorLock::orderOrLock ≠ "" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Current Window ]
#
#
End If
