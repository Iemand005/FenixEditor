#ifndef FEVULKANWINDOW_H
#define FEVULKANWINDOW_H

#include <QVulkanWindow>
#include <QVulkanInstance>

class FEVulkanWindow : public QVulkanWindow
{
public:
    FEVulkanWindow();


    // void initSwapChainResources() override {
    //     QSize size = swapChainImageSize();
    //     m_engine->resize(size.width(), size.height());
    // }

    // // Stap 3: De Render Loop (Elk frame aangeroepen door Qt)
    // void startNextFrame() override {
    //     VkCommandBuffer cmdBuf = currentCommandBuffer();
    //     VkExtent2D extent = { (uint32_t)swapChainImageSize().width(), (uint32_t)swapChainImageSize().height() };
    //     VkImage backBuffer = swapChainImage(currentSwapChainImageIndex());

    //     // Laat jouw engine renderen in de door Qt beheerde command buffer
    //     m_engine->render(cmdBuf, backBuffer, extent);

    //     // Geef het frame terug aan Qt om te presenteren aan het scherm
    //     frameReady();
    // }

    // void releaseResources() override {
    //     m_engine->cleanup();
    // }
};

#endif // FEVULKANWINDOW_H
