sharedMainLayoutScripts: backToLearnOrDefaultSetup
Allow User Abort [ Off ]
Set Error Capture [ On ]
Set Variable [ $$referenceRecordOne ]
Set Variable [ $$referenceSort ]
Set Variable [ $$ﬁndMode ]
If [ Left ( $$defaultTagLayout ; 1 ) = "d" ]
#
#Go to testlearn layout and loop back to record.
Set Window Title [ Current Window; New Title: "Setup" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Go to Field [ ]
#
#Check for any dragged changes to tag spellings.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#organ
Perform Find [ Speciﬁed Find Requests: Find Records; Criteria: tagMenus::match: “organ” ]
[ Restore ]
#copyist
Extend Found Set [ Speciﬁed Find Requests: Find Records; Criteria: tagMenus::match: “copyist” ]
[ Restore ]
#heatlh
Extend Found Set [ Speciﬁed Find Requests: Find Records; Criteria: tagMenus::match: “health” ]
[ Restore ]
#node
Extend Found Set [ Speciﬁed Find Requests: Find Records; Criteria: tagMenus::match: “node” ]
[ Restore ]
Perform Script [ “insureEqualityOfSpellFields” ]
#
#Go to Learn tag menu layout and loop back to record.
Set Variable [ $$stopAddTagToCitation; Value:1 ]
Go to Layout [ “defaultSections” (ruleSection) ]
Go to Record/Request/Page [ $$defaultRecordNumber ]
[ No dialog ]
Set Variable [ $$stopAddTagToCitation ]
Set Variable [ $$defaultRecordNumber ]
Set Variable [ $$defaultTagLayout ]
Set Variable [ $$citationMatch; Value:"section" ]
Perform Script [ “defaultSectionMenu” ]
Exit Script [ ]
End If
#
#Go to testlearn layout and loop back to record.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Window Title [ Current Window; New Title: "Learn" ]
If [ tempSetup::layoutLmain = "" ]
Go to Layout [ “learn1” (testlearn) ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
Go to Layout [ Middle ( tempSetup::layoutLmain ; 5 ; 42 ) ]
End If
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$LearnEdit = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadCitation ]
#
#Go to Learn tag menu layout and loop back to record.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
Go to Layout [ $$learnTagLayout ]
Set Variable [ $$learnTagLayout ]
Set Variable [ $$stopLoadTagRecord ]
If [ $$citeORref = "ref" ]
Perform Script [ “menuReference” ]
Else
Perform Script [ “menuRefAddKeyWords” ]
End If
#
If [ $$citeORref = "cite" ]
Set Variable [ $$citationMatch; Value:"cite" ]
Else If [ $$citeORref = "ref" ]
Set Variable [ $$citationMatch; Value:"ref" ]
End If
Select Window [ Name: "Learn"; Current ﬁle ]
#
#Perform Load Citation script to restore conditional
#formatting.
Perform Script [ “loadCitation” ]
January 7, 平成26 18:05:32 Imagination Quality Management.fp7 - backToLearnOrDefaultSetup -1-
