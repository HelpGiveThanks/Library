reference(citation): openCitationURL
#
#Show folder ﬁle is in.
If [ refReference::URL ≠ "" or
refReference::ISBN ≠ "" or
refReference::ISSN ≠ "" or
refReference::URLdoi ≠ "" ]
If [ ValueCount ( testlearn::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'QV' button in the Learn window or the 'references' button in the Tag Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: "Reference's Title: " & refReference::Title; Buttons: “OK” ]
Open URL [ Case ( refReference::URL ≠ "" ; refReference::URL ;
refReference::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refReference::ISBN ;
refReference::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refReference::ISSN ;
refReference::URLdoi ≠ "" ; "http://dx.doi.org/" & refReference::URLdoi ;
"") ]
[ No dialog ]
End If
#
#Show folder ﬁle is in.
If [ citeCite::URL ≠ "" or
citeCite::ISBN ≠ "" or
citeCite::ISSN ≠ "" or
citeCite::URLdoi ≠ "" ]
Show Custom Dialog [ Message: "Reference's Title: " & citeCite::Title; Buttons: “OK” ]
Open URL [ Case ( citeCite::URL ≠ "" ; citeCite::URL ;
citeCite::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & citeCite::ISBN ;
citeCite::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & citeCite::ISSN ;
citeCite::URLdoi ≠ "" ; "http://dx.doi.org/" & citeCite::URLdoi ;
"") ]
[ No dialog ]
End If
#
#Show folder ﬁle is in.
If [ citeTest::URL ≠ "" or
citeTest::ISBN ≠ "" or
citeTest::ISSN ≠ "" or
citeTest::URLdoi ≠ "" ]
Show Custom Dialog [ Message: "Reference's Title: " & citeTest::Title; Buttons: “OK” ]
Open URL [ Case ( citeTest::URL ≠ "" ; citeTest::URL ;
citeTest::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & citeTest::ISBN ;
citeTest::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & citeTest::ISSN ;
citeTest::URLdoi ≠ "" ; "http://dx.doi.org/" & citeTest::URLdoi ;
"") ]
[ No dialog ]
End If
#
#Show folder ﬁle is in.
If [ refTest::URL ≠ "" or
refTest::ISBN ≠ "" or
refTest::ISSN ≠ "" or
refTest::URLdoi ≠ "" ]
If [ ValueCount ( testlearnReportTags::kcreference ) > 1 ]
Show Custom Dialog [ Message: "This is the ﬁrst reference attached to this record. To see all references, click the 'edit/new' button in the main list view window, and once you are in the Learn module, click the 'QV' button in the Learn window or the 'references' button in the Learn Tag
Menus window."; Buttons: “OK” ]
End If
Show Custom Dialog [ Message: "Reference's Title: " & refTest::Title; Buttons: “OK” ]
Open URL [ Case ( refTest::URL ≠ "" ; refTest::URL ;
refTest::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTest::ISBN ;
refTest::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTest::ISSN ;
refTest::URLdoi ≠ "" ; "http://dx.doi.org/" & refTest::URLdoi ;
"") ]
[ No dialog ]
End If
January 7, 平成26 17:59:07 Imagination Quality Management.fp7 - openCitationURL -1-
