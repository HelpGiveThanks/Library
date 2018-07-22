July 21, 2018 14:41:44 Library.fmp12 - helpSetupTagCopyrightReview -1-
help: setup: helpSetupTagCopyrightReview
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"Setup" ]
Set Variable [ $$helpColumnName; Value:"H" ]
#
#Inform user they must cancel the find before
#they will be able to go to the help window as
#in find mode the focus is locked on it until
#the find is complete.
Show Custom Dialog [ Message: "If you are OK with exiting this interface to navigate to its help column — " & $$helpColumnName & "
— click OK. The system is locked while its focused on this interface, which is why exiting it is requried."; Default Button: “OK”,
Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
If [ Get (LastMessageChoice) = 1 ]
#
#This next variable prevents the user getting
#asked redunant questions by the help script.
Set Variable [ $$gotoHelpObject; Value:1 ]
Close Window [ Current Window ]
Perform Script [ “help (update)” ]
Set Variable [ $$gotoHelpObject ]
#
#Tell user how to get the help for this interface
#if they choose to remain focused on it.
Else
Show Custom Dialog [ Message: "To view help for this interface once you are done with it 1) click any ? button. 2) Click the
return button if given that option. 3) Click the Help App's menu button. 3) Click — " & $$helpLayoutName & "."; Default
Button: “OK”, Commit: “Yes” ]
Pause/Resume Script [ Indefinitely ]
End If
#
