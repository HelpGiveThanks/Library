January 18, 2018 15:38:17 Library.fmp12 - loadLearnOrRefMainRecord -1-
reference: loadLearnOrRefMainRecord
#
#
#This first section is key to stopping this script
#when another script for example loops thru
#many records each of which would trigger this
#script and really slow down the program and
#create strobe effect that is really irritating to
#look at.
If [ $$stoploadCitation = 1 ]
Exit Script [ ]
End If
#
#
#Admin tasks.
Set Variable [ ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If user clicked in the key word menu field
#(when selecting this record) and so activiated
#the script that loads the key tag menu, stop
#it from being loaded.
Set Variable [ $$stopTgotoCitationMenu; Value:1 ]
#
#These steps effect the button action where when the
#use clicks on the actual text box of a learn record
#a new window opens just displaying the text. This
#stops this when the user was clicking on it to select
#this record instead of adding text to it.
If [ Get (LayoutName) = "learn0" or
Get (LayoutName) = "learn1" or
Get (LayoutName) = "learn2" or
Get (LayoutName) = "learn3" or
Get (LayoutName) = "learn4" or
Get (LayoutName) = "learn5" or
Get (LayoutName) = "learnStuff0" or
Get (LayoutName) = "learnStuff1" or
Get (LayoutName) = "learnStuff2" or
Get (LayoutName) = "learnStuff3" or
Get (LayoutName) = "learnStuff4" or
Get (LayoutName) = "learnStuff5" ]
Set Variable [ $$stopOpenNewTextWindow; Value:1 ]
End If
#
#This key effects the conditional formatting
#of any records in the Tag Menus window
#that are related to the citation record that triggered
#this script (by the user click on it, of course).
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$main; Value:testlearn::_Ltestlearn ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagBrainstorm ]
Else If [ $$citationMatch = "key" ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Else If [ $$citationMatch = "ref" ]
Set Variable [ $$citationItem; Value:testlearn::kcreference ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagBrainstorm ]
Else If [ $$citationMatch = "test" ]
Set Variable [ $$citationItem; Value:testlearn::kctestSubsectionInfo ]
Else If [ $$citationMatch = "brainstorm" ]
Set Variable [ $$citationItem; Value:testlearn::kcbrainstorm ]
End If
#
#capture keys of related tag menu items to
#to allow the citationMenu scripts to loop to the
#primary record of interest when the user navigates
#to a item on the Tag Menu window
#whose list of tags like node, keyword, medium, etc.
#might contain an item related to the current
#citation record, but which one, which is why all
#the keys have to be readied. Mmm... now that
#I write this out, I'm thinking I could have the
#citationMenu scripts select the citation window
#to grab the key if any in the current current
#record that applies the the menu item.
Set Variable [ $$citationRecord; Value:testlearn::_Ltestlearn ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
Set Variable [ $$primaryNode; Value:testlearn::kNodePrimary ]
Set Variable [ $$copyright; Value:testlearn::kcopyright ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $windowName; Value:Get (WindowName) ]
#
#Note if record is locked to protect its tags.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Set Variable [ $$lockedMainLearnRecord; Value:tagTLNodePrimary::tag ]
Else
Set Variable [ $$lockedMainLearnRecord ]
End If
Commit Records/Requests
#
If [ $$add = "" and $$DuplicateDontGoToTagMenuWindow = "" ]
#Match any records in tag window and go to
#primary tag record or to first record if none.
#And don't run LoadTagRecord until matching is
#done to prevent flashing and slowing down script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
Perform Script [ “TgotoCitationMenu” ]
End If
Refresh Window
Go to Field [ ]
End If
Set Variable [ $$DuplicateDontGoToTagMenuWindow ]
#
#
#
#
#
Else If [ Get (LastError) ≠ 112 ]
#
#Get reference groups and references order
#number in case user changes it.
Set Variable [ $$refGroupOrderNumber; Value:tagKeywordPrimary::orderOrLock ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
#
#Get record number so if during the editing of
#this record its alphabetical order should
#change, the library will sort the window to
#keep the user focused on the changed
#record.
Set Variable [ $$referenceRecordPosition; Value:Get ( RecordNumber ) ]
#
Set Variable [ $$main; Value:reference::_Lreference ]
Set Field [ TEMP::ReferenceFolder; reference::kfileLocation ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:reference::knodePrimary ]
Else If [ $$citationMatch = "medium" ]
Set Variable [ $$citationItem; Value:reference::kmedium ]
Else If [ $$citationMatch = "Path" ]
Set Variable [ $$citationItem; Value:reference::kfolderpath ]
Else If [ $$citationMatch = "key" ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
Else If [ $$citationMatch = "publication" ]
Set Variable [ $$citationItem; Value:reference::kpublication ]
Else If [ $$citationMatch = "publisher" ]
Set Variable [ $$citationItem; Value:reference::kpublisher ]
Else If [ $$citationMatch = "copyright" ]
Set Variable [ $$citationItem; Value:reference::kCopyright ]
Else If [ $$citationMatch = "cite" ]
Set Variable [ $$citationItem; Value:reference::kcitation ]
Else If [ $$citationMatch = "ref" ]
Set Variable [ $$citationItem; Value:testlearn::kcreference ]
End If
#
#capture keys of related tag menu items to
#to allow the citationMenu scripts to loop to the
#primary record of interest when the user navigates
#to a item on the Tag Menu window
#whose list of tags like node, keyword, medium, etc.
#might contain an item related to the current
#citation record, but which one, which is why all
#the keys have to be readied. Mmm... now that
#I write this out, I'm thinking I could have the
#citationMenu scripts select the citation window
#to grab the key if any in the current current
#record that applies the the menu item.
Set Variable [ $$citationRecord; Value:reference::_Lreference ]
Set Variable [ $$node; Value:reference::knodeOther ]
Set Variable [ $$primaryNode; Value:reference::knodePrimary ]
Set Variable [ $$publication; Value:reference::kpublication ]
Set Variable [ $$publisher; Value:reference::kpublisher ]
Set Variable [ $$medium; Value:reference::kmedium ]
Set Variable [ $$copyright; Value:reference::kCopyright ]
Set Variable [ $$CopyrightType; Value:reference::kcopyrightType ]
Set Variable [ $$Path; Value:reference::kfolderpath ]
Set Variable [ $$cite; Value:reference::kcitation ]
Set Variable [ $$ref; Value:reference::lock ]
Set Variable [ $$PrimaryKey; Value:reference::kkeywordPrimary ]
Set Variable [ $$Key; Value:reference::kkeywordOther ]
Set Variable [ $$OtherKey; Value:reference::kkeywordOther ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $windowName; Value:Get (WindowName) ]
#
#
#Note if record is locked to protect its tags.
If [ refCreatorNode::orderOrLock ≠ "" ]
Set Variable [ $$lockedMainRefRecord; Value:refCreatorNode::tag ]
Else
Set Variable [ $$lockedMainRefRecord ]
End If
#
#Stop user getting locked record message by
#turning of the exit script that will be triggered
#once this record commits.
Set Variable [ $$turnOffRefStuffExitScript; Value:1 ]
Commit Records/Requests
Set Variable [ $$turnOffRefStuffExitScript ]
#
If [ $$add = "" ]
#Match any records in tag window and go to
#primary tag record or to first record if none.
#And don't run LoadTagRecord until matching is
#done to prevent flashing and slowing down script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
Perform Script [ “TgotoCitationMenu” ]
End If
Refresh Window
End If
End If
#
#Return to observation or reference window.
Set Variable [ $$stopLoadTagRecord ]
Select Window [ Name: $windowName; Current file ]
Refresh Window
#
#
#Purplefy Learn layout Find Button!
#If user is loading a learn record, then check
#if any learn records reference it and if so
#set a variable to conditionally format the learn
#window's 'find' button purple to indicate this.
If [ Get ( WindowName ) = "Learn" ]
Set Variable [ $$stoploadCitation; Value:1 ]
New Window [ Name: "LinkedLearnRecords"; Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”;
Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Name: "LinkedLearnRecords"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control
Area: “Yes”; Resize: “Yes” ]
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$main ]
Perform Find [ ]
#
If [ Get (LastError) = 401 ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$LinkedLearnRecords ]
Set Variable [ $$stopTgotoCitationMenu; Value:1 ]
Close Window [ Name: "LinkedLearnRecords"; Current file ]
Refresh Window
Exit Script [ ]
End If
#
Set Variable [ $$LinkedLearnRecords; Value:Get (FoundCount) ]
#
Set Variable [ $$stoploadCitation ]
Close Window [ Name: "LinkedLearnRecords"; Current file ]
#
Refresh Window
End If
#
Set Variable [ $$stopTgotoCitationMenu ]
#
