help: help
#
#
// Close Window [ Name: "Help" ]
#
#Set back path from help to this solution.
Set Field [ MemorySwitch::backToSolution; "Library" ]
#
#
#Set tag menu variable to 1 if user is on tag menu, and
#then select the main window to determin the module.
If [ Get (WindowName) = "Tag Menus" ]
If [ $$findMode = 1 ]
Set Field [ MemorySwitch::helpObjectName; "find" ]
Else
If [ $$citationMatch = "copyist" or $$citationMatch = "path" or $$citationMatch = "organ" ]
Set Field [ MemorySwitch::helpObjectName; "key" ]
Else
Set Field [ MemorySwitch::helpObjectName; $$citationMatch ]
End If
#
If [ Get (LayoutName) = "testMenuTestItem" ]
Set Field [ MemorySwitch::helpObjectName; "test item" ]
Else If [ Get (LayoutName) = "testInfo" ]
Set Field [ MemorySwitch::helpObjectName; "test info" ]
Else If [ Get (LayoutName) = "reportTagDiscovery" ]
Set Field [ MemorySwitch::helpObjectName; "result" ]
Else If [ Get (LayoutName) = "reportTagItem" ]
Set Field [ MemorySwitch::helpObjectName; "item" ]
Else If [ Get (LayoutName) = "reportTagInfo" ]
Set Field [ MemorySwitch::helpObjectName; "info" ]
Else If [ Get (LayoutName) = "setupTestFocus" ]
Set Field [ MemorySwitch::helpObjectName; "section" ]
End If
#
End If
Set Variable [ $tagWindow; Value:1 ]
Select Window [ Name: "Setup"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Select Window [ Name: "Print/Copy"; Current file ]
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Test"; Current file ]
Select Window [ Name: "Report"; Current file ]
End If
#
#Determin the module.
If [ Get ( LayoutTableName ) = "tempSetup" ]
Set Field [ MemorySwitch::helpLayoutName; "Setup" ]
Else If [ Get ( LayoutTableName ) = "testLearn" and Get (LayoutName) ≠ "step4_InspectionFinding" ]
Set Field [ MemorySwitch::helpLayoutName; "Learn" ]
Else If [ Get ( LayoutTableName ) = "reference" ]
Set Field [ MemorySwitch::helpLayoutName; "Reference" ]
Else If [ Get ( LayoutTableName ) = "test" ]
Set Field [ MemorySwitch::helpLayoutName; "Test" ]
Else If [ Get ( LayoutTableName ) = "inspectItems" ]
Set Field [ MemorySwitch::helpLayoutName; "Test" ]
Else If [ Get ( LayoutTableName ) = "testLearn" and Get (LayoutName) = "step4_InspectionFinding" ]
Set Field [ MemorySwitch::helpLayoutName; "Test" ]
Else If [ Get ( LayoutTableName ) = "report" ]
Set Field [ MemorySwitch::helpLayoutName; "Test" ]
End If
#
If [ $tagWindow ≠ 1 ]
#Help for library setup module main window.
If [ Get (LayoutName) = "defaultSetup" ]
Set Field [ MemorySwitch::helpObjectName; "library" ]
End If
#
#Help for test setup module main window.
If [ Get (LayoutName) = "testSetup" ]
Set Field [ MemorySwitch::helpObjectName; "setup" ]
End If
#
#Help for test select main window.
If [ Get (LayoutName) = "step3_InspectionItems" ]
Set Field [ MemorySwitch::helpObjectName; "test select" ]
End If
#
#Help for test select main window.
If [ Get (LayoutName) = "step4_InspectionFinding" ]
Set Field [ MemorySwitch::helpObjectName; "test finding" ]
End If
#
#Help for report main window.
If [ Get (LayoutName) = "PrintReportEdit" ]
Set Field [ MemorySwitch::helpObjectName; "report" ]
End If
#
#Help for learn module main window.
If [ Get (LayoutName) = "learn1" or Get (LayoutName) = "learn2" or Get (LayoutName) = "learn3" or Get (LayoutName) = "learn4" ]
Set Field [ MemorySwitch::helpObjectName; "learn" ]
Else If [ Get (LayoutName) = "LearnTextWindow" ]
Set Field [ MemorySwitch::helpObjectName; "edit" ]
Show Custom Dialog [ Message: "This edit-note window will be closed while you view help for this window. Your work will be saved! When you are finished viewing help, click on your text to re-open this window and continue editing."; Buttons: “cancel”, “OK” ]
If [ Get ( LastMessageChoice ) = 1 ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
Else
Close Window [ Current Window ]
End If
Else If [ Get (LayoutName) = "Learn4EDIT" ]
Set Field [ MemorySwitch::helpObjectName; "qv" ]
Else If [ Get (LayoutName) = "learnFind" ]
Set Field [ MemorySwitch::helpObjectName; "learnFind" ]
Else If [ Get (LayoutName) = "learnPreviewLayout" ]
Set Field [ MemorySwitch::helpObjectName; "print" ]
#
#Help for reference module main window.
Else If [ Get (LayoutName) = "reference" ]
Set Field [ MemorySwitch::helpObjectName; "ref" ]
Else If [ Get (LayoutName) = "referenceEdit" ]
Set Field [ MemorySwitch::helpObjectName; "ref edit" ]
Else If [ Get (LayoutName) = "referenceFind" ]
Set Field [ MemorySwitch::helpObjectName; "ref find" ]
End If
End If
#
#
January 7, 平成26 18:12:57 Imagination Quality Management.fp7 - help -1-help: help
Pause/Resume Script [ Duration (seconds): .1 ]
#
Open URL [ MemorySwitch::helpPath ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "file://" ; "file:///Volumes/" ) ]
[ No dialog ]
#
Select Window [ Name: "Help" ]
Select Window [ Name: "Tutorial" ]
#
#
January 7, 平成26 18:12:57 Imagination Quality Management.fp7 - help -2-
