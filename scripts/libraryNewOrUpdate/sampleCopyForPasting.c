libraryNewOrUpdate: sampleCopyForPasting
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#I commonly click the share button when I do not mean
#click it, so these next two question help the user
#stop this process if it was not intential. They also
#help the user understand that if they proceed how long
#it is likely to take, so they don't become frustrated.
If [ Get ( FoundCount ) > 999 and Get ( LayoutName ) ≠ "learn4EDIT" ]
Show Custom Dialog [ Message: "FYI: There are more than 1000 records to process. This may take a few minutes. Continue?"; Buttons: “Yes”, “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
End If
If [ Get ( FoundCount ) > 100 and Get ( LayoutName ) ≠ "learn4EDIT" ]
Show Custom Dialog [ Message: "FYI: There are more than 100 and less than 1000 records to process. This may take a minute or more. Continue?"; Buttons: “Yes”, “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
End If
#
#Begin process of show user selected records and their references.
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $layoutName; Value:Get ( LayoutName ) ]
Close Window [ Name: "Print/Copy"; Current file ]
New Window [ Name: "Print/Copy" ]
Go to Layout [ “learnMenuSample” (tagMenus) ]
If [ $$citationMatch = "sample" ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $$tagsample ]
Perform Find [ ]
If [ tagMenus::notesOrHealth = "" ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Print/Copy"; Current file ]
Show Custom Dialog [ Message: "Select a copyright from the pulldown menu for your theory in the Tag Menus window. If you are making a case, you probably need to select a no-remix copyright so all your points and evidence are kept together by anyone copying your work."; Buttons:
“OK” ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
Else If [ Get (LastError) = 400 ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
End If
End If
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
#If user is in QV, then find any linked learn records.
If [ $layoutName = "learn4EDIT" ]
Set Variable [ $findLinkedLearnRecords; Value:testlearn::_Ltestlearn ]
Loop
Go to Object [ Object Name: "ref2" ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $findLinkedLearnRecords; Value:refTestLearn::_Ltestlearn & ¶ & $findLinkedLearnRecords ]
Go to Portal Row
[ Select; Next; Exit after last ]
End Loop
#
#Determine how many keys there are.
Set Variable [ $numberOfKeys; Value:ValueCount ($findLinkedLearnRecords ) ]
#
#Find 1st record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Perform Find [ ]
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
#
If [ $numberOfKeys ≠ 0 ]
Go to Layout [ “learn4EDIT” (testlearn) ]
Show Custom Dialog [ Message: "The ideas expressed in this record are linked to ideas from previous records. Do you want to also see these?"; Buttons: “Yes”, “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
#
#Loop thru each key to expand found records until
#all linked records have been found.
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeys = 0 ]
#
#Find record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Extend Found Set [ ]
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
#
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Else
Go to Layout [ “learnPreviewLayout” (testlearn) ]
End If
End If
#
End If
#
#Now gather up and add references linked to all records.
Set Variable [ $point; Value:1 ]
Set Variable [ $evidence; Value:1 ]
Go to Record/Request/Page
[ First ]
#
Loop
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence &
//node
TextColor (
Case ( testlearn::kcitation ≠ "" ; " Quote from cited work below." ;
 " [" &
Case ( tagTLNodePrimary::tag = "" and testlearn::NodeOthers = "" ; TextStyleAdd ( "author not entered" ; Italic ) ;
tagTLNodePrimary::tag ≠ "" ; tagTLNodePrimary::tag ) &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers) &
//timestamp
" " & testlearn::timestamp & "]" )
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) ;
$point & TextFont ( testlearn::Caption ; "Georgia" ) ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"keywords - " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) ) &
//URL
Case ( testlearn::URL ≠ "" ; ¶ & testlearn::URL &
//URLdate
Case ( testlearn::URLPubDate ≠ "" ; " (link validated " & testlearn::URLPubDate & ")" ; " (link validity unavailable)") ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
February 24, 平成26 10:30:14 Imagination Quality Management.fp7 - sampleCopyForPasting -1-libraryNewOrUpdate: sampleCopyForPasting
Set Variable [ $copy; Value://previous records
Case ( $copy = "" ; "" ; $copy & ¶ & ¶) &
//text
Case ( testlearn::sampleCasePoint = "" ; $point & "." & $evidence &
//node
TextColor (
Case ( testlearn::kcitation ≠ "" ; " Quote from cited work below." ;
 " [" &
Case ( tagTLNodePrimary::tag = "" and testlearn::NodeOthers = "" ; TextStyleAdd ( "author not entered" ; Italic ) ;
tagTLNodePrimary::tag ≠ "" ; tagTLNodePrimary::tag ) &
Case ( testlearn::NodeOthers = "" ; "" ; "; " & testlearn::NodeOthers) &
//timestamp
" " & testlearn::timestamp & "]" )
 ; RGB ( 119 ; 119 ; 119 ) ) & ¶ &
//main text
TextFont ( testlearn::Caption ; "Georgia" ) ;
$point & TextFont ( testlearn::Caption ; "Georgia" ) ) & ¶ &
//grey remain text
TextColor (
//keyword
Case ( testlearn::OtherKeyWords ≠ "" or testlearn::kKeywordPrimary ≠ "" ; ¶ &
"keywords - " &
//primary keyword
tagTLKeywordPrimary::tag &
Case ( testlearn::OtherKeyWords = "" ; "" ;
//other keyword
Case ( testlearn::kKeywordPrimary ≠ "" ; ", " & testlearn::OtherKeyWords ; testlearn::OtherKeyWords ) ) ) &
//URL
Case ( testlearn::URL ≠ "" ; ¶ & testlearn::URL &
//URLdate
Case ( testlearn::URLPubDate ≠ "" ; " (link validated " & testlearn::URLPubDate & ")" ; " (link validity unavailable)") ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
#
#Increase evidence number if point is the same.
If [ testlearn::sampleCasePoint = "" ]
Set Variable [ $evidence; Value:$evidence + 1 ]
Else
Set Variable [ $evidence; Value:1 ]
End If
If [ testlearn::kcreference ≠ "" ]
Go to Object [ Object Name: "ref1" ]
If [ refReference::referenceForReferenceWindow ≠ "" ]
Set Variable [ $copy; Value:$copy & ¶ &
//grey text
TextColor (
//references
Case ( testlearn::kcreference ≠ "" ; "References" ; "" )
//finsih text color
 ; RGB ( 119 ; 119 ; 119 ) ) ]
Loop
Go to Object [ Object Name: "ref1" ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $copy; Value:Case ( Right ( $copy ; 10 ) = "References" ;
$copy & ¶ &
//grey text
TextColor ( refReference::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ;
$copy & ¶ & ¶ &
//grey text
TextColor ( refReference::referenceForReferenceWindow ; RGB ( 119 ; 119 ; 119 ) ) ) ]
Go to Portal Row
[ Select; Next; Exit after last ]
End Loop
End If
End If
Go to Record/Request/Page
[ Next; Exit after last ]
Set Variable [ $copy; Value:$copy & ¶ &
//grey text
TextColor ( "_______________________________________________" ; RGB ( 119 ; 119 ; 119 ) ) ]
Exit Loop If [ (
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 1 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 2 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 3 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 4 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 5 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 6 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 7 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 8 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 9 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 10 ) ; 4 ; 42 ) ; $$tagSample & "¶" ) = $$tagSample & ¶
) ≠ 1 and $$tagSample ≠ "" ]
#
#Increase point number if point is different.
If [ testlearn::sampleCasePoint ≠ "" ]
Set Variable [ $point; Value:$point + 1 ]
End If
End Loop
#
#Now get sample title and previous dates of
#publication for this sample if there are any.
If [ $$citationMatch = "Sample" ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $sample; Value://Sample Title
TextStyleAdd ( tagMenus::tag ; Titlecase ) & ¶ &
Case ( learnSampleWebsite::URLPubDate = "" ;
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" & Year ( Get ( CurrentDate ) ) & " " ;
//author and copyright
nodeLockTagMenus::tag & " " & Month ( learnSampleWebsite::URLPubDate ) & "/" & Day ( learnSampleWebsite::URLPubDate ) & "/" & Year ( learnSampleWebsite::URLPubDate ) & " " ) &
sampleCopyright::tag & " " &
//title for history
¶ & "Publication History" &
Case ( learnSampleWebsite::URL = "" ; ¶ & "(This posting is the first publication of this version of the theory and presentation of supporting evidence.)" ) ]
// Set Variable [ $sample; Value://Sample Title
$sample & ¶ & sampleCopyright::tag & " " & Month ( learnSampleWebsite::URLPubDate ) & "/" & Day ( learnSampleWebsite::URLPubDate ) & "/" & Year ( learnSampleWebsite::URLPubDate ) & " by " & nodeLockTagMenus::tag ]
Loop
Go to Object [ Object Name: "publication" ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $sample; Value:$sample & ¶ &
Case ( learnSampleWebsite::URLPubDate = "" ;
learnSampleWebsite::URL ;
learnSampleWebsite::URL & " " & Month ( learnSampleWebsite::URLPubDate ) & "/" & Day ( learnSampleWebsite::URLPubDate ) & "/" & Year ( learnSampleWebsite::URLPubDate ) ) ]
Go to Portal Row
[ Select; Next; Exit after last ]
End Loop
Go to Field [ ]
Set Variable [ $copy; Value://Sample Title and History
$sample & ¶ & ¶ & $copy ]
#
#Now create copy text and display it.
Select Window [ Name: "Print/Copy"; Current file ]
Else
February 24, 平成26 10:30:14 Imagination Quality Management.fp7 - sampleCopyForPasting -2-libraryNewOrUpdate: sampleCopyForPasting
If [ $layoutName = "learn4EDIT" ]
Set Variable [ $sample; Value://author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" & Year ( Get ( CurrentDate ) ) & " " ]
Else
Set Variable [ $sample; Value://Sample Title
"Unsaved group of records ordered by date and time of creation!!! This action is not advised for publishing purposes. Instead, use the theorize tag to create a saved set of records ordered by you to make the strongest case you can make for publishing sets of records." & ¶ &
//author and copyright date
TEMP::DEFAULTNodePrimaryName & " " & Month ( Get ( CurrentDate ) ) & "/" & Day ( Get ( CurrentDate ) ) & "/" & Year ( Get ( CurrentDate ) ) & " " ]
End If
Go to Layout [ “TEMP” (TEMP) ]
Set Variable [ $sample; Value:$sample &
//health/copyright
defaultCopyrightName::tag ]
Go to Layout [ “learnPreviewLayout” (testlearn) ]
Set Variable [ $copy; Value://Sample Title and History
$sample & ¶ & ¶ & $copy ]
End If
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Set Field [ TEMP::paste; TextSize ( $copy ; 12 ) ]
Go to Field [ ]
Scroll Window
[ Home ]
February 24, 平成26 10:30:14 Imagination Quality Management.fp7 - sampleCopyForPasting -3-
