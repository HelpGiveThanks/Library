September 10, 2018 16:36:08 Library.fmp12 - helpAllApps -1-
help: helpAllApps
#
#
#
#
// If [ MemorySwitch::name = "" ]
Show Custom Dialog [ Message: "Most of these buttons open an application, library, or website when clicked, with the exception
of the add, back, info, X, and ? buttons."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Click the add and X buttons to add and delete libraries from the Libraries list. Click info to open
this app's info window. Click back to return to the previous interface, and ? to see this help."; Default Button: “OK”, Commit:
“Yes” ]
Show Custom Dialog [ Message: "NOTE: Periodically check the HelpGiveThanks website to insure that you are using the most
current version of each application and library. Version numbers are displayed vertically."; Default Button: “OK”, Commit:
“Yes” ]
// Else
// Show Custom Dialog [ Message: "Click any button to open that application, library, or website. Click the add button to add
libraries to the list of libraries that you can open."; Default Button: “OK”, Commit: “Yes” ]
// End If
Exit Script [ ]
#
#
#
#
#
#Send general layout name and help column
#number to the help script so it can take the
#user to help for this layout and column.
Set Variable [ $$helpLayoutName; Value:"All Apps" ]
Set Variable [ $$helpColumnName; Value:"A" ]
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
Perform Script [ “help” ]
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
#
