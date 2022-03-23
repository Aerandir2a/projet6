// ...

//App init

SDL_GLContext context = SDL_GL_CreateContext(win);
SDL_GL_MakeCurrent(win, context);

IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

ImGui_ImplSDL2_InitForOpenGL(win, context);
ImGui_ImplOpenGL2_Init();

ImGui::StyleColorsDark();


//...

//SDL event pump 

SDL_Event curEvent;
while (SDL_PollEvent(&curEvent))
{
    ImGui_ImplSDL2_ProcessEvent(&curEvent);
    if (!io.WantCaptureMouse)
    {
        //use mouse events not already used by ImGui
    }
    if (!io.WantCaptureKeyboard)
    {
        //use keyboard events not already used by ImGui
    }
    //... app processing other events;
}

//...

//Render Loop
ImGui_ImplOpenGL2_NewFrame();
ImGui_ImplSDL2_NewFrame(win);

ImGui::NewFrame();

// Draw some widgets

ImGui::Begin("Perfs");
ImGui::LabelText("Frame Time (ms) : ", "%f", elapsedSeconds * 1e-3);
ImGui::LabelText("FPS : ", "%f", 1.0 / elapsedSeconds);
ImGui::End();

//....

//... App rendering

//Rendering end

ImGui::Render();
ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

//Swap window as usual
SDL_GL_SwapWindow(win);
