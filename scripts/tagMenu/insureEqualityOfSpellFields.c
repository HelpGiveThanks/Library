tagMenu: insureEqualityOfSpellFields
#
#
If [ $$stopTest = 1
//or $$citationMatch = "key"
//or $$citationMatch = "node"
//or $$citationMatch = "health"
or $$citationMatch = "path"
//or tagLocation::match = "focus" and nodeLockTest::orderOrLock = "" ]
Exit Script [ ]
End If
#
If [ Get (LayoutTableName) = "tagMenus" ]
#
#Exit any fields so do not get can't modify error message
#because record is in use in another window.
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
// New Window [ Top: 1; Left: 1 ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has then change it back
#to the way it was, unless the change was made in the
#field the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
#Test group name.
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling
and
Get (LayoutTableName) = "test"
and
nodeLockTagMenus::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "testGroup" ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
End If
#Test item group name.
If [ ruleTagMenuTestGroups::name ≠ ruleTagMenuTestGroups::defaultSectionInfo
and
Get (LayoutTableName) ≠ "test"
and
nodeLockTestTagGroup::orderOrLock ≠ "" and
ruleTagMenuTestGroups::nameSpelling = "testItemGroup" ]
Set Field [ ruleTagMenuTestGroups::name; ruleTagMenuTestGroups::defaultSectionInfo ]
End If
#Sample group name.
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling
and
nodeLockTagGroup::orderOrLock ≠ ""
and
ruleTagMenuGroups::match = "sample" ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
End If
#Health locked group name.
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling
and
ruleTagMenuGroups::order ≠ ""
and
ruleTagMenuGroups::match = "health" ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
End If
// #Allow user to change name of group, just not tag for:
#Sample, health, node, key, copyist, organ, testItem locked group name.
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and nodeLockTagGroup::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "node"
 or ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and nodeLockTagGroup::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "key"
 or ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and nodeLockTagGroup::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "sample"
 or ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and nodeLockTagGroup::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "copyist"
 or ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and nodeLockTagGroup::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "organ"
 or ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling and nodeLockTagGroup::orderOrLock ≠ "" and
ruleTagMenuGroups::match = "testItem" ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
End If
#Sample, health, node, key, copyist, organ, testItem tag names.
If [ tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "testItem"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "sample"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "health"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "organ"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "node"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "copyist"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "key" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
#Locked by system health tags.
If [ tagMenus::orderOrLock ≠ "" and tagMenus::match = "health" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
#
#But if node is not locked, then apply changes to field.
#Group name.
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling
and
Get (LayoutTableName) = "test"
 and
nodeLockTagMenus::orderOrLock = "" and
ruleTagMenuGroups::match = "testGroup" ]
Set Field [ ruleTagMenuGroups::nameSpelling; ruleTagMenuGroups::name ]
End If
#Test item group name.
If [ ruleTagMenuTestGroups::name ≠ ruleTagMenuTestGroups::defaultSectionInfo and
Get (LayoutTableName) ≠ "test"
 and
nodeLockTagMenus::orderOrLock = "" and
ruleTagMenuTestGroups::nameSpelling = "testItemGroup" ]
Set Field [ ruleTagMenuTestGroups::defaultSectionInfo; ruleTagMenuTestGroups::name ]
End If
#Sample group name.
If [ ruleTagMenuGroups::name ≠ ruleTagMenuGroups::nameSpelling
and
nodeLockTagGroup::orderOrLock = ""
and
ruleTagMenuGroups::match = "sample" ]
Set Field [ ruleTagMenuGroups::nameSpelling; ruleTagMenuGroups::name ]
End If
#Sample, health, node, copyist, organ, testItem, key, tag names.
If [ tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "testItem"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "sample"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "health"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "organ"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "copyist"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "node"
 or tagMenus::tag ≠ tagMenus::tagSpelling and nodeLockTagMenus::orderOrLock = "" and tagMenus::match = "key" ]
Set Field [ tagMenus::tagSpelling; tagMenus::tag ]
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
#But first set this stop variable, so if locked field is
#is a group name field its name will not be changed.
Set Variable [ $$stopChangeName; Value:1 ]
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$stopTest; Value:1 ]
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
#Test group name.
If [ groupTest::name ≠ groupTest::nameSpelling and nodeLockTestGroup::orderOrLock ≠ "" and
groupTest::match = "testGroup" ]
Set Field [ groupTest::name; groupTest::nameSpelling ]
End If
#Test name.
If [ test::testName ≠ test::testNameRevert and nodeLockTest::orderOrLock ≠ "" ]
Set Field [ test::testName; test::testNameRevert ]
End If
If [ test::testName ≠ test::testNameRevert and nodeLockTest::orderOrLock = "" ]
Set Field [ test::testNameRevert; test::testName ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Current Window ]
Else If [ Get (LayoutTableName) = "tagLocation" ]
#Get spelling change if any to change just the
#current record if not locked.
Set Variable [ $sectionTemplateSpelling; Value:Get (ActiveFieldContents) ]
#
#Exit any fields so do not get can't modify error message
#because record is in use in another window.
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has then change it back
#to the way it was, unless the change was made in the
#field the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
If [ tagLocation::tag ≠ tagLocation::tagSpelling and nodeLockTest::orderOrLock ≠ "" and tagLocation::match = "focus"
or
$sectionTemplateSpelling ≠ tagLocation::tag ]
Set Field [ tagLocation::tag; tagLocation::tagSpelling ]
End If
#
#But if node is not locked, then apply changes to
#field user was just in if any changes where made.
If [ tagLocation::tag ≠ tagLocation::tagSpelling and nodeLockTest::orderOrLock = "" and tagLocation::match = "focus" and
$sectionTemplateSpelling = tagLocation::tag ]
Set Field [ tagLocation::tagSpelling; tagLocation::tag ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Current Window ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID ]
Exit Script [ ]
End If
Set Variable [ $$stopTest ]
Set Variable [ $$ID ]
Perform Script [ “loadSetupTestRecord” ]
August 19, ଘ౮28 23:22:22 Library.fp7 - insureEqualityOfSpellFields -1-
