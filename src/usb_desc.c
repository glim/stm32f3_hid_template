/**
  ******************************************************************************
  * @file    USB_Example/usb_desc.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Descriptors for Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t Hid_DeviceDescriptor[HID_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize 64*/
    0x83,                       /*idVendor (0x0483)*/
    0x04,
    0x10,                       /*idProduct = 0x5710*/
    0x57,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                                  manufacturer */
    2,                          /*Index of string descriptor describing
                                                 product*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* Hid_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Hid_ConfigDescriptor[HID_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    HID_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /*bNumInterfaces: 1 interface*/
    0x01,         /*bConfigurationValue: Configuration value*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                     the configuration*/
    0xE0,         /*bmAttributes: bus powered */
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

    /************** Descriptor of Hid Mouse interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size*/
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
    0x00,         /*bInterfaceNumber: Number of Interface*/
    0x00,         /*bAlternateSetting: Alternate setting*/
    0x02,         /*bNumEndpoints*/
    0x03,         /*bInterfaceClass: HID*/
    0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,            /*iInterface: Index of string descriptor*/
    /******************** Descriptor of Hid Mouse HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size*/
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
    0x11,         /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,         /*bCountryCode: Hardware target country*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
    0x22,         /*bDescriptorType*/
    HID_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
    0x00,
    /******************** Descriptor of Hid Mouse endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x81,          /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,          /*bmAttributes: Interrupt endpoint*/
    USB_PACKET_SIZE,          /*wMaxPacketSize: 4 Byte max */
    0x00,
    0x20,          /*bInterval: Polling Interval (32 ms)*/
    /* 34 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x01,          /*bEndpointAddress: Endpoint Address (OUT)*/
    0x03,          /*bmAttributes: Interrupt endpoint*/
    USB_PACKET_SIZE,          /*wMaxPacketSize: 4 Byte max */
    0x00,
    0x20,          /*bInterval: Polling Interval (32 ms)*/
    /* 34 */

  }
  ; /* MOUSE_ConfigDescriptor */
const uint8_t Hid_ReportDescriptor[HID_SIZ_REPORT_DESC] =
  {


		  0x06, 0x00, 0xFF,       // Usage Page = 0xFF00 (Vendor Defined Page 1)
		     0x09, 0x01,             // Usage (Vendor Usage 1)
		     0xA1, 0x01,             // Collection (Application)
		     0x19, 0x01,             //      Usage Minimum
		     0x29, USB_PACKET_SIZE,             //      Usage Maximum 	//64 input usages total (0x01 to 0x40)
		     0x15, 0x01,             //      Logical Minimum (data bytes in the report may have minimum value = 0x00)
		     0x25, USB_PACKET_SIZE,      	  	//      Logical Maximum (data bytes in the report may have maximum value = 0x00FF = unsigned 255)
		     0x75, 0x08,             //      Report Size: 8-bit field size
		     0x95, USB_PACKET_SIZE,             //      Report Count: Make sixty-four 8-bit fields (the next time the parser hits an "Input", "Output", or "Feature" item)
		     0x81, 0x00,             //      Input (Data, Array, Abs): Instantiates input packet fields based on the above report size, count, logical min/max, and usage.
		     0x19, 0x01,             //      Usage Minimum
		     0x29, USB_PACKET_SIZE,             //      Usage Maximum 	//64 output usages total (0x01 to 0x40)
		     0x91, 0x00,             //      Output (Data, Array, Abs): Instantiates output packet fields.  Uses same report size and count as "Input" fields, since nothing new/different was specified to the parser since the "Input" item.
		     0xC0                   // End Collection
  }
  ; /* Hid_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t Hid_StringLangID[HID_SIZ_STRING_LANGID] =
  {
    HID_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t Hid_StringVendor[HID_SIZ_STRING_VENDOR] =
  {
    HID_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t Hid_StringProduct[HID_SIZ_STRING_PRODUCT] =
  {
    HID_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'J', 0,
    'o', 0, 'y', 0, 's', 0, 't', 0, 'i', 0, 'c', 0, 'k', 0
  };
uint8_t Hid_StringSerial[HID_SIZ_STRING_SERIAL] =
  {
    HID_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '1', 0, '0', 0
  };


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
