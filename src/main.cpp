// https://arthursonzogni.github.io/FTXUI/examples_2component_2dropdown_8cpp-example.html
#include <memory>  // for shared_ptr, __shared_ptr_access
#include <string>  // for operator+, to_string
#include <unistd.h>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/node.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/screen/color.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
 
using namespace ftxui;
 
int main(int argc, const char* argv[]) {
  int value = 50;
  Component input_list = Container::Vertical({});
  std::vector<std::string> items(3, "");
  for (int i = 0; i < items.size(); i++) {
      input_list->Add(Input(&(items[i]), "place" + std::to_string(i)));

  }

  // The tree of components. This defines how to navigate using the keyboard.
  auto buttons = Container::Horizontal({
      Button("Decrease", [&] { value--; }),
      Button("Increase", [&] { value++; }),
      input_list
  });
  buttons->Add(Button("tt", []{}));
 
  // Modify the way to render them on screen:
  auto component = Renderer(buttons, [&] {
    return vbox({
               text("value = " + std::to_string(value)),
               separator(),
               gauge(value * 0.01f),
               separator(),
               buttons->Render(),
           }) |
           border;
  });
 
  auto screen = ScreenInteractive::FitComponent();
  auto document =  //
      hbox({
              vbox({
                      text("Line 1"),
                      text("Line 2"),
                      text("Line 3"),
                      }) | border,

              vbox({
                      text("Line 4"),
                      text("Line 5"),
                      text("Line 6"),
                      }) | border,

              vbox({
                      text("Line 7"),
                      text("Line 8"),
                      text("Line 9"),
                      }) | border,
              });
  auto screen2 = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen2, document);
  screen2.Print();

  screen.Loop(component);
  return 0;
}
