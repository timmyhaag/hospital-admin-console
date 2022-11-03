# Hospital Administration Console App
A full console application is written which mimics a hospital emergency room triage (very simplified) that has two major functions: cataloging/reporting of patient information and simulation of “treating” patients.

"Triaging" patients is by priority order, and then first come, first serve. Priority is an integer, with lower number being a higher priority. E.g. 1 is higher than 10. 

“Treating” a patient is marking them as treated and removing them from the triaged container and inserting them into a treated container, as well as some random thread sleep interval from 1 to 3 seconds to "simulate" time passing. E.g. if you have 100 patients, it won't magically mark everyone as treated right away.

The program is presenting a text-based user interface, and will have a main loop that won't exit unless you ask it to. 
