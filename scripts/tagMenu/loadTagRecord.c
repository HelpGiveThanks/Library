August 4, 2018 14:17:32 Library.fmp12 - loadTagRecord -1-
tagMenu: loadTagRecord
#
#NOTE: this script is used on the Tag Menus window
#for Learn records to exit field when a record is
#is first entered, which is a real problem on the
#iPhone as the text edit box opens when the user
#may have clicked only to select the record rather
#than edit it.
# The 'Go to field' exit command is in the citation load
#script along with a lot of other commands which
#are not needed for Tag records. I chose this
#smaller script, which also has conditional formatting
#step which is not used here, but is needed on
#on other layouts.
# SO...light script with unused command instead
#of heavy script orginally written for loading these
#records when they are main records (here they
#are just tag records).
#
If [ $$stopLoadTagRecord ≠ ""
 or
$$goBackToSetup ≠ ""
 or
$$returnToSetup ≠ "" ]
Exit Script [ ]
End If
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Set Variable [ $$ifScriptRunsHalfSecondAfterThisOneHaltIt ]
#
#When user has navigated to a key tag menu
#record by clicking on the order-number
#popup menu, set this variable to insure the
#order number selection process is completed.
If [ Get ( ActiveFieldName ) = "orderOrLock" and $$citationMatch = "key" ]
Set Variable [ $$keyOrderNumberPossibleChanged; Value:1 ]
End If
#
#On the test-item layout, set this stop check
#or text variable to allow the user to click into
#this field for the purpose of navigating to a
#new record without changing the check or
#text mark status.
If [ $$citationMatch = "testItem" and Get ( ActiveFieldName ) ≠ "tag" ]
Set Variable [ $$stopCheckOrTest; Value:1 ]
Else
Set Variable [ $$stopCheckOrTest ]
End If
#
#Stop warning message on file path tag menu.
Set Variable [ $$stopFilePathWarning; Value:1 ]
#
#Exit the field. This allows user to just
#navigate the record without the text box
#staying opening, unless they want that to
#happen BUT ONLY on test item layouts.
Set Variable [ $$stopTest; Value:1 ]
If [ tagMenus::match = "testItem" ]
If [ $$showAll ≠ 1 ]
Go to Field [ ]
End If
Else If [ tagMenus::match ≠ "testItem" ]
Go to Field [ ]
Set Variable [ $$stopGoToKeyTag; Value:1 ]
End If
Set Variable [ $$stopTest ]
#
#Start warning message on file path tag menu.
Set Variable [ $$stopFilePathWarning ]
#
#Capture recordID to conditionally format current record.
Set Variable [ $$tagRecordID; Value:Get (RecordID) ]
#
#Clear the old record's ID so its hidden edit
#fields do not get revealed during navigation.
Set Variable [ $$editLocation ]
#
#Get tag's group key for 'move' button script.
Set Variable [ $$groupOLD; Value:tagMenus::kGroupOrTest ]
#
#Delete tag group order number if user selects
#delete order number option when they
#navigated to this record.
If [ $$citationMatch = "key" and tagMenuGroup::orderOrLibraryType = "delete number"
 or
$$citationMatch = "node" and tagMenuGroup::orderOrLibraryType = "delete number" ]
Set Field [ tagMenuGroup::orderOrLibraryType; "" ]
End If
#
#Delete tag order number if user selects
#delete order number option.
If [ $$citationMatch = "key" and tagMenus::orderOrLock = "delete number"
 or
$$citationMatch = "testItem" and tagMenus::orderOrLock = "delete number"
 or
Get (LayoutTableName) and tagKeywordPrimary::orderOrLock = "delete number" ]
If [ Get (LayoutTableName) and tagKeywordPrimary::orderOrLock = "delete number" ]
Set Field [ tagKeywordPrimary::orderOrLock; "" ]
Else
Set Field [ tagMenus::orderOrLock; "" ]
End If
End If
#
#Get reference groups and references order
#number in case user changes it.
Set Variable [ $$refGroupOrderNumber; Value:tagKeywordPrimary::orderOrLock ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
Set Variable [ $$refIDForMainLearnRecord; Value:reference::_Lreference ]
#
#Refresh the window so hidden fields that must
#match the ID variable just updated will now
#show up.
Refresh Window
#
#
#Clear these variables and then load them.
Set Variable [ $$refIDForMainLearnRecord ]
Set Variable [ $$learnIDForMainLearnRecord; Value:reference::_Lreference ]
Set Variable [ $$refIDForMainLearnRecord; Value:reference::_Lreference ]
If [ TEMP::layoutLmain = "lesslearn4"
or
TEMP::layoutLmain = "morelearn4"
or
$$testLearnLayoutName ≠ "" ]
Select Window [ Name: "Learn"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#Get tag's copyright key for 'select' button
#in case this node is locked, and the copyright
#has to be put back to the orginal after the
#user is informed they cannot change a locked
#record's copyright.
Set Variable [ $$oldCopyright; Value:tagMenus::notesOrCopyright ]
#
#When going the Learn or the Reference
#section, this script is run towards the end,
#and this Halt Script bit needs to be stopped
#from proceeding until these sections are
#completely loaded. Otherwise, when going
#to them the user ends up focused on the Tag
#Menus key menu, instead of on the main
#Learn or Reference window.
If [ $$doNotHaltOtherScripts = "" ]
#
#When going to a new tag covered by this next
#bit of script, SOMETIMES FileMaker will launch
#the enterShortOrLongTagField script*, which
#allows empty picture fields to be hidden, and
#the tag's text box to appear longer, basically
#covering up the unused picture field. *(When
#a user is NOT in a text field prior to clicking
#on a different tag record, FileMaker launches
#that script.)
# Now, upon loading a new tag record the
#launching of this script MUST happen, in
#order to allow the user to navigate without
#opening a text field. So first step below does
#that. But if FileMaker also starts up this
#script, it will run twice cause problems, so the
#Halt command will stop this script for
#running twice by cancelling all scripts that are
#set to run.
If [ $$citationMatch = "ref"
 or
$$citationMatch = "key"
 or
$$citationMatch = "node" ]
Perform Script [ “enterShortOrLongTagField” ]
#
#If there is media, then open the media window,
#but if not then halt this script, just in case the
#user clicked on a button when navigating. The
#halt command will stop that button's script
#from running.
If [ $$citationMatch = "ref" and reference::picture = "" and reference::showMedia = "" and reference::showMedia[2] = ""
 and
tagMenus::Kpicture1 = "" and tagMenus::match ≠ "testItem" ]
#
#Use this message when testing to see if this
#loadTagRecord script is halting other scripts
#that really need to run.
// Show Custom Dialog [ Title: "halt"; Message: "halt"; Default Button: “OK”, Commit: “Yes” ]
Halt Script
Else
#
#This variable is used by any scripts that where
#started by navigating to the current tag record
#which started this script, except the open
#media window script. The other scripts
#running right after this one will test if less than
#a second has past since this variable was set,
#and if so they will exit (not run).
Set Variable [ $$ifScriptRunsHalfSecondAfterThisOneHaltIt; Value:Get ( CurrentTime ) ]
End If
End If
#
End If
#
#Clear the order number check variable.
Set Variable [ $$keyOrderNumberPossibleChanged ]
#
#
