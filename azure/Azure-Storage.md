# Azure Storage Service
https://learn.microsoft.com/en-us/rest/api/storageservices/

## Azure Storage Create by Azure Portal
Go to https://portal.azure.com
<div style="float:left;width:100%;clear:both;"><img src="doc-image/step-0000.png" style="width:50%;margin-left:25%;"></div>

Then select from left side menu `Storage accounts` and inside click on tab `Create`
<div style="float:left;width:100%;clear:both;"><img src="doc-image/step-0001.png" style="width:50%;margin-left:25%;"></div>




## Azure Storage Create by Azure CLI

Login to Azure account and go to `portal.azure.com/#blade/HubsExtension/BrowseResourceGroups` and on top navigation menu click on `Cloud Shell`

### https://learn.microsoft.com/es-es/cli/azure/ad/sp?view=azure-cli-latest

### https://learn.microsoft.com/es-es/cli/azure/ad/sp?view=azure-cli-latest#az-ad-sp-create-for-rbac()

Create Azure Service Principle add the following commands
```bash
$ az ad sp create-for-rbac --name test_storageAccount
The output includes credentials that you must protect. Be sure that you do not include these credentials in your code or check the credentials into your source control. For more information, see https://aka.ms/azadsp-cli
{
  "appId": "0gfa8bbe-9fde-4df5-a096-d8f0482c003e",
  "displayName": "azure-cli-2023-10-17-13-58-00",
  "password": "P1R8Q~AFAMxyuM2o46WqtIasdasddUojhI4-qbTD",
  "tenant": "f8e4b634-e90f-4306-7894-0010756e7168"
}
```

Create a resoruce group
```bash
$ az group create --location westus --name test_storageAccount
...
{
  "id": "/subscriptions/fa628409-adf4-fasd8-afde-7b509d932bbd/resourceGroup/test_storageAccount",
  "location": "westus",
  "manageBy": "test_storageAccount",
  "name": "",
  "properties": {
    "provisioningState": "Succeded"
  },
  "tags": "null",
  "type": "Microsoft.Resources/resourcesGroups"
}
```

Get Access Token
```bash

```

## Postman Colletions for Azure Storage

enviroment.postman_environment.json
```json
{
	"id": "",
	"name": "",
	"values": [
		{
			"key": "client_id",
			"value": "",
			"enabled": true
		},
		{
			"key": "client_secret",
			"value": "",
			"enabled": true
		},
		{
			"key": "tenantid",
			"value": "",
			"enabled": true
		},
		{
			"key": "resource",
			"value": "",
			"enabled": true
		},
		{
			"key": "subscriptionId",
			"value": "",
			"enabled": true
		},
		{
			"key": "resourceGroupName",
			"value": "",
			"enabled": true
		},
		{
			"key": "accountName",
			"value": "",
			"enabled": true
		},
		{
			"key": "access_token",
			"value": "",
			"enabled": true
		},
		{
			"key": "grant_type",
			"value": "",
			"enabled": true
		}
	],
	"_postman_variable_scope": "environment",
	"_postman_exported_at": "2023-10-17T12:25:19.673Z",
	"_postman_exported_using": "Postman/9.0.2"
}
```

account.postman_collection.json
```json
{
	"info": {
		"_postman_id": "bfba77ea-dd5a-40a4-93f8-4a603619df84",
		"name": "Azure Storage Account",
		"schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json"
	},
	"item": [
		{
			"name": "Get Access Token",
			"event": [
				{
					"listen": "test",
					"script": {
						"exec": [
							"var data = JSON.parse(responseBody);\r",
							"postman.setEnvironmentVariable(\"access_token\", data.access_token);"
						],
						"type": "text/javascript"
					}
				}
			],
			"protocolProfileBehavior": {
				"disableBodyPruning": true
			},
			"request": {
				"method": "GET",
				"header": [],
				"body": {
					"mode": "urlencoded",
					"urlencoded": [
						{
							"key": "client_id",
							"value": "{{client_id}}",
							"type": "text"
						},
						{
							"key": "grant_type",
							"value": "{{grant_type}}",
							"type": "text"
						},
						{
							"key": "client_secret",
							"value": "{{client_secret}}",
							"type": "text"
						},
						{
							"key": "resource",
							"value": "{{resource}}",
							"type": "text"
						}
					]
				},
				"url": {
					"raw": "https://login.microsoftonline.com/{{tenantid}}/oauth2/token",
					"protocol": "https",
					"host": [
						"login",
						"microsoftonline",
						"com"
					],
					"path": [
						"{{tenantid}}",
						"oauth2",
						"token"
					]
				}
			},
			"response": []
		},
		{
			"name": "Create Storage Account",
			"request": {
				"auth": {
					"type": "bearer",
					"bearer": [
						{
							"key": "token",
							"value": "{{access_token}}",
							"type": "string"
						}
					]
				},
				"method": "PUT",
				"header": [],
				"body": {
					"mode": "raw",
					"raw": "{\r\n  \"sku\": {\r\n    \"name\": \"Standard_GRS\"\r\n  },\r\n  \"kind\": \"StorageV2\",\r\n  \"location\": \"australiaeast\"\r\n}",
					"options": {
						"raw": {
							"language": "json"
						}
					}
				},
				"url": {
					"raw": "https://management.azure.com/subscriptions/{{subscriptionId}}/resourceGroups/{{resourceGroupName}}/providers/Microsoft.Storage/storageAccounts/{{accountName}}?api-version=2018-02-01",
					"protocol": "https",
					"host": [
						"management",
						"azure",
						"com"
					],
					"path": [
						"subscriptions",
						"{{subscriptionId}}",
						"resourceGroups",
						"{{resourceGroupName}}",
						"providers",
						"Microsoft.Storage",
						"storageAccounts",
						"{{accountName}}"
					],
					"query": [
						{
							"key": "api-version",
							"value": "2018-02-01"
						}
					]
				}
			},
			"response": []
		}
	]
}
```