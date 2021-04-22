1. How do I approach designing software?
   * What new design skills has your work on the project helped you to craft?
      * I would say the design skills that have definetly improved is writing code in a reusable fashion. Given that we had to render multiple objects as a part of this scene, and that there positions in 3D space would be different, it doesn't make sense to hand generate vertex data for these objects. It made sense to generate the shape and transform its position and scale programtically.
   * What design process did you follow for your project work?
      * I went through this process iteratively. For example, I worked on the texture loading and got one texture per object to load. Then I made a further iteration when adding the dictionary to keep track of all open texture program's so they can be safetly destroyed later. Then I performed another revision and added the ability to load multiple skins per object type. Finally, I added the ability for those skins to be rendered at random to make the scene more interesting.
   * How could tactics from your design approach be applied in future work?
      * I like the design approach 'iterate fast and crash' as it can truely lead to some out-of-the-box type idea's. Sometimes finding out an idea won't work early in the process prevents a future time sink in trying to make that subsystem work. 
2. How do I approach developing programs?
   * What new development strategies did you use while working on your 3D scene?
      * I used a form of test driven design in order to work on the vertex buffers for my scene. I head a seperate application that I used to show the geometry without the fancy lighting and texturing to make sure the polygones were drawn in a way that I expected them.
   * How did iteration factor into your development?
      * Hugely! As mentioned above, I approached each subsystem in an iterative fashion. This allowed me to quickly flesh out what idea's did and did not work, and buuld systems that 'worked' from hour zero. It may not have all the functionality initially, but you get an idea on the direction of a subsytem and if it will utimately be successful.
   * How has your approach to developing code evolved throughout the milestones, which led you to the project’s completion?
      * Each milestone for me ended up being an interative cycle. It worked out that I approached each milestone slightly different and sometimes it lead to cool inovation.
3. How can computer science help me in reaching my goals?
   * How do computational graphics and visualizations give you new knowledge and skills that can be applied in your future educational pathway?
      * While I do see the value of working with graphic and visualizations, I do not believe it will significantly impact my future educational pathway. As I am nearing the end of my bachalor's degree, the time to utilize this skill in the educational realm is quickly decreasing. 
   * How do computational graphics and visualizations give you new knowledge and skills that can be applied in your future professional pathway?
      * Sometimes I may come across a project that requires me to render models or images in a 3D environment. This could be in displaying the results of data or maybe even a 3d walkthrough for building plans. Working om this project has opened my eyes into how to make something like that even work.
