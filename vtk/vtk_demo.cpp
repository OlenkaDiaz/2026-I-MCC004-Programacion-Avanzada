#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main() {
    // Crear un cono.
    vtkNew<vtkConeSource> cono;
    cono->SetHeight(3.0);
    cono->SetRadius(1.0);
    cono->SetResolution(50);

    // Preparar los datos para mostrarlos.
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cono->GetOutputPort());

    // Crear el objeto que se mostrara.
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    // Crear el espacio de visualizacion.
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    // Crear la ventana.
    vtkNew<vtkRenderWindow> ventana;
    ventana->AddRenderer(renderer);
    ventana->SetWindowName("Demo VTK - Cono");
    ventana->SetSize(800, 600);

    // Permitir interaccion con el mouse.
    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(ventana);

    ventana->Render();
    interactor->Start();

    return 0;
}