tagMenu: CHUNKcheckForDragPasteChanges
#Used by script changeSpellingOfKeywordOrNodeTag
#
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
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has change it back
#to the way it was, unless the change was made in the
#field the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and
$$Tag ≠ ruleTagMenuGroups::_Lgroup and
Get (LayoutName) ≠ "setupTestItem" and
Length ( ruleTagMenuGroups::match ) < 12 ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
End If
If [ ruleTagMenuTestGroups::name ≠ ruleTagMenuTestGroups::defaultSectionInfo and
$$Tag ≠ ruleTagMenuTestGroups::_Lgroup and
Get (LayoutName) = "setupTestItem" and
ruleTagMenuTestGroups::nameSpelling = "testItemGroup" ]
Set Field [ ruleTagMenuTestGroups::name; ruleTagMenuTestGroups::defaultSectionInfo ]
End If
If [ tagMenus::tag ≠ tagMenus::tagSpelling and $$Tag ≠ tagMenus::_Ltag and tagMenus::match = "node" or
tagMenus::tag ≠ tagMenus::tagSpelling and $$Tag ≠ tagMenus::_Ltag and tagMenus::match = "key" or
tagMenus::tag ≠ tagMenus::tagSpelling and $$Tag ≠ tagMenus::_Ltag and tagMenus::match = "testItem" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Current Window ]
Else If [ Get (LayoutTableName) = "test" ]
#
#Exit any fields so do not get can't modify error message
#because record is in use in another window.
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$ID; Value:"ignore" ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has change it back
#to the way it was, unless the change was made in the
#field the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
If [ groupTest::name ≠ groupTest::nameSpelling and $$GroupTag ≠ groupTest::_Lgroup and
groupTest::match = "testGroup" ]
Set Field [ groupTest::name; groupTest::nameSpelling ]
End If
If [ test::testName ≠ test::testNameRevert and $$Tag ≠ test::_Ltest ]
Set Field [ test::testName; test::testNameRevert ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
If [ $$tag ≠ "" ]
Set Variable [ $$ID; Value:$$tag ]
End If
Close Window [ Current Window ]
End If
January 7, 平成26 16:44:57 Imagination Quality Management.fp7 - CHUNKcheckForDragPasteChanges -1-
