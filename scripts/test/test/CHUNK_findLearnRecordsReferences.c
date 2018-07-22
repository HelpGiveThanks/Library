July 21, 2018 14:45:17 Library.fmp12 - CHUNK_findLearnRecordsReferences -1-
test: test: CHUNK_findLearnRecordsReferences
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the learn record has references then make sure
#the Reference window is open, and then load up
#its reference records, otherwise exit the script.
If [ Get (LayoutTableName) = "testlearnReportTags" ]
If [ testlearnReportTags::kcreference = ""
 or
ValueCount ( testlearnReportTags::kcreference ) - Length ( Filter ( testlearnReportTags::kcreference ; "L" ) ) = 0 ]
Exit Script [ ]
End If
Else
If [ testlearn::kcreference = ""
 or
ValueCount ( testlearn::kcreference ) - Length ( Filter ( testlearn::kcreference ; "L" ) ) = 0 ]
Exit Script [ ]
End If
End If
#
#Prevent halting to loadTagRecord script.
Go to Field [ ]
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Set Variable [ $$stopWhenLoadingInfoRecordReferences; Value:1 ]
#
#Capture the keys of the references load.
If [ Get (LayoutTableName) = "testlearnReportTags" ]
Set Variable [ $references; Value:testlearnReportTags::kcreference ]
Else
Set Variable [ $references; Value:testlearn::kcreference ]
End If
#
#Determine how many references there are.
If [ Get (LayoutTableName) = "testlearnReportTags" ]
Set Variable [ $numberOfReferences; Value:ValueCount ( testlearnReportTags::kcreference ) ]
Else
Set Variable [ $numberOfReferences; Value:ValueCount ( testlearn::kcreference ) ]
End If
#
#Prevent loading up records.
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#In the test section, go the Reference window
#or open one up if neccessary.
If [ Get (LayoutTableName) = "testlearnReportTags" ]
Select Window [ Name: "Reference"; Current file ]
If [ Get ( LastError ) = 112 ]
If [ $$pictureWindowColor = "test" ]
New Window [ Name: "Reference"; Width: Get ( ScreenWidth ) / 3; Left: ( Get ( ScreenWidth ) / 3 ) * 2; Style:
Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Else
New Window [ Name: "Reference"; Width: 290; Left: Get ( ScreenWidth ) - 290; Style: Document; Close: “Yes”;
Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
End If
End If
#
#Go the layout for info references.
Go to Layout [ “TestInfoReference” (reference) ]
#
#
Else
#In the learn section, go to the Tag Menus
#window and the reference layout.
Select Window [ Name: "Tag Menus"; Current file ]
#
#See if user has selected requested menu.
If [ Get (LayoutTableName) ≠ "reference" ]
#
#Menu NOT selected.
Go to Layout [ “learnMenu3CiteS” (reference) ]
End If
End If
#
#Turn back on record load script.
Set Variable [ $$stoploadtestinfo ]
#
#Find the first reference. NOTE: It may be this
#first reference is a learn reference, and so no
#records will be found, but this is OK. This first
#find clears out any records that may have
#been found previously, and replaces them with
#the outcome of this first find, which if none is,
#again, OK. Then next find step expands on
#this find, so to speed things up, it will not look
#for learn references, BUT if this step did not
#look for learn records, the script would in
#effect skip this first find and so leave in place
#the records found previously. Very Bad!
#NOTE: I've had a lot of caffeine.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; GetValue ( $references ; $numberOfReferences ) ]
Perform Find [ ]
#
#If there is more than one reference, then load
#find them one-at-time until all have been found.
Loop
Set Variable [ $numberOfReferences; Value:$numberOfReferences - 1 ]
#
Exit Loop If [ $numberOfReferences = 0 ]
#
#Only find references from the Reference section.
If [ Right ( GetValue ( $references ; $numberOfReferences ) ; 1 ) ≠ "L" ]
Enter Find Mode [ ]
Set Field [ reference::_Lreference; GetValue ( $references ; $numberOfReferences ) ]
Extend Found Set [ ]
End If
#
End Loop
#
#Sort the references by keyword (subject).
Perform Script [ “sortRefBySubject” ]
#
#In the test section ...
#Resize the Reference window along with the
#other windows. The Test and Report sections
#have different window size requirements.
If [ Get (WindowName) = "Reference" ]
If [ $$pictureWindowColor = "test" ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 3; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 3; Left: Get ( ScreenWidth ) / 3 ]
Select Window [ Name: "Tag Menus"; Current file ]
Else
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get ( ScreenWidth ) - 884 < 334 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: 334; Left: 594 ]
Else
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) - 884; Left: 594 ]
End If
End If
#
#Turn back on info record record's load script.
Set Variable [ $$stopWhenLoadingInfoRecordReferences ]
#
#
Else
#In the learn section ...
#Clear brainstorm and test tags so there conditional
#formatting in the Learn window is removed.
Go to Field [ ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
Set Field [ TEMP::TLBrainstormSort; "" ]
Set Field [ TEMP::TLTestSort; "" ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"ref" ]
#Goto correct layout.
#
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ TEMP::layoutLtagR = "" ]
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnMenu3CiteS” (reference) ]
Set Field [ TEMP::layoutLtagR; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnMenu3Cite” (reference) ]
Set Field [ TEMP::layoutLtagR; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagR ; 5 ; 42 ) ]
End If
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
End If
#
#
