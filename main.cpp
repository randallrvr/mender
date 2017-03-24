#include <mtlpp/mtlpp.hpp>

#include "window.hpp"
#include "MetalApp.h"

#include <vector>
#include <string>
//
//mtlpp::Device              g_device;
//mtlpp::CommandQueue        g_commandQueue;
//mtlpp::Buffer              g_vertexBuffer;
//mtlpp::RenderPipelineState g_renderPipelineState;
//
//void MyRender(const AppMacOS &app)
//{
//	// Get Command Buffer from Command Queue
//	mtlpp::CommandBuffer commandBuffer = g_commandQueue.CommandBuffer();
//
//	// Get Render Pass Description from window
//    mtlpp::RenderPassDescriptor renderPassDesc = app.GetRenderPassDescriptor();
//
//	if(renderPassDesc)
//    {
//		// Get Render Command Encoder
//        mtlpp::RenderCommandEncoder renderCommandEncoder = commandBuffer.RenderCommandEncoder(renderPassDesc);
//
//		// Set Render Pipeline State / Vertex Buffers / Draw Type
//		renderCommandEncoder.SetRenderPipelineState(g_renderPipelineState);
//        renderCommandEncoder.SetVertexBuffer(g_vertexBuffer, 0, 0);
//        renderCommandEncoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
//        renderCommandEncoder.EndEncoding();
//
//		// Draw
//        commandBuffer.Present(app.GetDrawable());
//    }
//
//    commandBuffer.Commit();
//    commandBuffer.WaitUntilCompleted();
//
//
//	cerr << "custom render func" << endl;
//}

int main(int argc, char *argv[])
{

	std::vector<std::string> args;
	for(int i = 1; i < argc; i++)
	{
		args.push_back(std::string(argv[i]));
	}

	MetalApp metalApp("Metal App", 1280, 720, args);


//	// Create Window and pass render function to it
//    Window win(g_device, &MyRender, 640, 480);
//
//	// Run
//    Window::Run();

//	metalApp.setRender(&MyRender);

	metalApp.run();

    return 0;
}

