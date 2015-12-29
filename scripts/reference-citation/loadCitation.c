reference(citation): loadCitation
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
#These steps effect the button action where when the
#use clicks on the actual text box of a learn record
#a new window opens just displaying the text. This
#stops this when the user was clicking on it to select
#this record instead of adding text to it.
If [ Get (LayoutName) = "learn1" or
Get (LayoutName) = "learn2" or
Get (LayoutName) = "learn3" or
Get (LayoutName) = "learn4" ]
Set Variable [ $$stopOpenNewTextWindow; Value:1 ]
End If
#
#
#SEE WHAT WAS REMOVED IN OLD VERSION.
#THE CODE REMOVED WAS DISABLED IN OLD VERSION.
#
#This key effects the conditional formatting
#of any records in the Tag Menus window
#that are related to the citation record that triggered
#this script (by the user click on it, of course).
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$citation; Value:testlearn::_Ltestlearn ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagSample ]
Else If [ $$citationMatch = "medium" ]
Set Variable [ $$citationItem; Value:testlearn::kmedium ]
Else If [ $$citationMatch = "Path" ]
Set Variable [ $$citationItem; Value:testlearn::kfolderPath ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagSample ]
Else If [ $$citationMatch = "key" ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Else If [ $$citationMatch = "health" ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagSample ]
Set Variable [ $$citationItem; Value:testlearn::kHealth ]
Else If [ $$citationMatch = "cite" ]
Set Variable [ $$citationItem; Value:testlearn::kcitation ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagSample ]
Else If [ $$citationMatch = "ref" ]
Set Variable [ $$citationItem; Value:testlearn::kcreference ]
Set Variable [ $$tagTest ]
Set Variable [ $$tagSample ]
Else If [ $$citationMatch = "test" ]
Set Variable [ $$citationItem; Value:testlearn::kctest ]
Else If [ $$citationMatch = "sample" ]
Set Variable [ $$citationItem; Value:testlearn::kcsample ]
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
Set Variable [ $$medium; Value:testlearn::kmedium ]
Set Variable [ $$health; Value:testlearn::kHealth ]
Set Variable [ $$Path; Value:testlearn::kfolderPath ]
Set Variable [ $$cite; Value:testlearn::kcitation ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Set Variable [ $$Section; Value:testlearn::kcsection ]
Set Variable [ $$test; Value:testlearn::kctest ]
Set Variable [ $$sample; Value:testlearn::kcsample ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $windowName; Value:Get (WindowName) ]
Commit Records/Requests
#
If [ $$add = "" ]
#Match any records in tag window and go to
#primary tag record or to first record if none.
#And don't run LoadTagRecord until matching is
#done to prevent flashing and slowing down script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
If [ Get (LastError) = 112 ]
Perform Script [ “TgotoCitationMenu” ]
End If
Refresh Window
// If [ $$citationMatch = "sample" ]
// #SEE WHAT WAS REMOVED IN OLD VERSION.
// #THE CODE REMOVED WAS DISABLED IN OLD VERSION.
// Else If [ $$citationMatch = "test" ]
// Go to Record/Request/Page
[ First ]
// Loop
// Set Variable [ $number; Value:1 ]
// Go to Field [ ]
// Loop
// Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" = test::_Ltest & ¶ ]
// Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) = "" ]
// Set Variable [ $add; Value:$number ]
// Set Variable [ $number; Value:$add + 1 ]
// End Loop
// Exit Loop If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" = test::_Ltest & ¶ ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ Middle ( GetValue ( $$test ; $number ) ; 4 ; 42 ) & "¶" ≠ test::_Ltest & ¶ ]
// Go to Record/Request/Page
[ First ]
// End If
// Else If [ $$citationMatch ≠ "sample" or $$citationMatch ≠ "test" ]
// Freeze Window
// Set Variable [ $$stopLoadTagRecord; Value:1 ]
// Go to Record/Request/Page
[ First ]
// Scroll Window
[ Home ]
// Loop
// Exit Loop If [ tagMenus::_Ltag = $$citationItem or FilterValues ( $$sample ; tagMenus::_Ltag & "¶" ) =
tagMenus::_Ltag & ¶ or
FilterValues ( $$test ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
reference::_Lreference = $$citationitem and $$citationMatch = "cite" or
reference::_Lreference & "¶" = FilterValues ( $$ref ; reference::_Lreference & "¶" ) and $$citationMatch =
"ref"
 or
testlearn::_Ltestlearn = $$citationitem and $$citationMatch = "cite"or
testlearn::_Ltestlearn & "¶" = FilterValues ( $$ref ; testlearn::_Ltestlearn & "¶" ) and $$citationMatch = "ref"
 or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "node"
or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "key" ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ Get (LastError) = 101 ]
// Go to Record/Request/Page
[ First ]
// Scroll Window
[ Home ]
// End If
// End If
// #
// Set Variable [ $$stopLoadTagRecord ]
// If [ Right (Get (LayoutName) ; 1 ) = "r" ]
// Perform Script [ “loadTagRecord” ]
// Else If [ $$citationMatch = "sample" ]
// #SEE WHAT WAS REMOVED IN OLD VERSION.
// #THE CODE REMOVED WAS DISABLED IN OLD VERSION.
// Else If [ $$citationMatch = "test" ]
// If [ testlearn::kctest ≠ "" ]
// Perform Script [ “loadItemRecordForTestTagMenu” ]
// End If
// End If
End If
#
#
#
#
#
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$citation; Value:reference::_Lreference ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:reference::knodePrimary ]
Else If [ $$citationMatch = "medium" ]
Set Variable [ $$citationItem; Value:reference::kmedium ]
Else If [ $$citationMatch = "Path" ]
Set Variable [ $$citationItem; Value:reference::kfolderpath ]
Else If [ $$citationMatch = "key" ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
Else If [ $$citationMatch = "organ" ]
Set Variable [ $$citationItem; Value:reference::korgan ]
Else If [ $$citationMatch = "copyist" ]
Set Variable [ $$citationItem; Value:reference::kcopyist ]
Else If [ $$citationMatch = "health" ]
Set Variable [ $$citationItem; Value:reference::kHealth ]
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
Set Variable [ $$organ; Value:reference::korgan ]
Set Variable [ $$copyist; Value:reference::kcopyist ]
Set Variable [ $$medium; Value:reference::kmedium ]
Set Variable [ $$health; Value:reference::kHealth ]
Set Variable [ $$CopyrightType; Value:reference::kcopyrightType ]
Set Variable [ $$Path; Value:reference::kfolderpath ]
Set Variable [ $$cite; Value:reference::kcitation ]
Set Variable [ $$ref; Value:reference::lock ]
Set Variable [ $$PrimaryKey; Value:reference::kkeywordPrimary ]
Set Variable [ $$Key; Value:reference::kkeywordOther ]
Set Variable [ $$OtherKey; Value:reference::kkeywordOther ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $windowName; Value:Get (WindowName) ]
Commit Records/Requests
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
// Go to Record/Request/Page
[ First ]
// #SEE WHAT WAS REMOVED IN OLD VERSION.
// #THE CODE REMOVED WAS DISABLED IN OLD VERSION.
// Loop
// Exit Loop If [ tagMenus::_Ltag = $$citationItem or FilterValues ( $$sample ; tagMenus::_Ltag & "¶" ) = tagMenus::
_Ltag & ¶ or
FilterValues ( $$test ; test::_Ltest & "¶" ) = test::_Ltest & ¶
 or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "node"
or
tagMenus::_Ltag = $$citationitem and $$citationMatch = "key" ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ Get (LastError) = 101 ]
// Go to Record/Request/Page
[ First ]
// End If
// Set Variable [ $$stopLoadTagRecord ]
// Perform Script [ “loadTagRecord” ]
End If
End If
#
#Return to observation or reference window.
Set Variable [ $$stopLoadTagRecord ]
Select Window [ Name: $windowName; Current file ]
Refresh Window
#
#
#If user is loading a learn record, then check
#if it references any learn records and if so
#set a variable to conditionally format the learn
#window's 'find' button purple to indicate this.
If [ Get ( WindowName ) = "Learn" ]
Set Variable [ $$stoploadCitation; Value:1 ]
// New Window [ Name: "LinkedLearnRecords"; Height: 1; Width: 1; Top: -1000; Left: -1000 ]
New Window [ Name: "LinkedLearnRecords" ]
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$citation ]
Perform Find [ ]
#
If [ Get (LastError) = 401 ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$LinkedLearnRecords ]
Close Window [ Name: "LinkedLearnRecords"; Current file ]
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
#
#
#
December 28, ଘ౮27 17:33:49 Library.fp7 - loadCitation -1-
